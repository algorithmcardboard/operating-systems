#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

#include "ds/event_queue.cpp"
#include "ds/io_request.cpp"
#include "ds/state.h"

#include "schedulers/abstract_scheduler.cpp"
#include "schedulers/fifo.cpp"
#include "schedulers/sstf.cpp"
#include "schedulers/scan.cpp"
#include "schedulers/cscan.cpp"
#include "schedulers/fscan.cpp"

using namespace std;

AbstractScheduler* getAlgorithm(char algoChar){
  AbstractScheduler* algo;
  switch(algoChar){
    case 'i':
      algo = new FIFO();
      break;
    case 'j':
      algo = new SSTF();
      break;
    case 's':
      algo = new SCAN();
      break;
    case 'c':
      algo = new CSCAN();
      break;
    case 'f':
      algo = new FSCAN();
      break;
  }
  return algo;
}

int main(int argc, char** argv){
  bool verbose = false, fscan = false, request_details = false;
  char c;

  char* inputFile;
  ifstream* inFile;
  string tmp;
  AbstractScheduler *absScheduler = NULL;
  vector<IoRequest*> io_requests;
  EventQueue eve_queue;


  unsigned int nextIOTime = 0;

  while((c = getopt(argc, argv, "s:vfd:")) != -1){
    switch(c){
      case 's':
        absScheduler = getAlgorithm(*(optarg+0));
        break;
      case 'v':
        verbose = true;
        break;
      case 'f':
        fscan = true;
        break;
      case 'd':
        request_details = true;
        break;
    }
  }

  if(absScheduler == NULL){
    cout << "Algorithm required" << endl;
    exit(99);
  }

  if(argc - optind != 1){
    cout << "Input file required" << endl;
    exit(99);
  }

  inputFile = argv[optind];
  inFile = new ifstream(inputFile);

  if(!inFile->good()){
    cout << "Not a valid input file" << endl;
    exit(99);
  }

  unsigned int time = 0;
  unsigned int track = 0;
  while(*(inFile) >> tmp){
    if(tmp[0] == '#'){
      getline(*(inFile), tmp);
      continue;
    }
    stringstream(tmp) >> time;
    *(inFile) >> track;
    IoRequest* request = new IoRequest(time, track);
    io_requests.push_back(request);
    Event* event = new Event(time, track, request->getId(), ADD);
    eve_queue.push(event);
  }

  if(verbose){
    cout << "TRACE" << endl;
  }
  Event* cur_event;
  unsigned int cur_time = 0, cur_track = 0, total_movement = 0;
  unsigned int track_movement = 0;
  IoRequest* req = NULL;
  while((cur_event = eve_queue.pop()) != NULL){
    cur_time  = cur_event->getTimestamp();
    switch(cur_event->getOperation()){
      case ADD:
        absScheduler->add_track_request(io_requests[cur_event->getId()]);
        if(verbose){
          cout << cur_event->getTimestamp() << ":" 
            << setw(6) << setfill(' ') << cur_event->getId() << " add " << cur_event->getTrack() << endl;
        }
        break;
      case ISSUE:
        req = io_requests[cur_event->getId()];
        req->setIssueTime(cur_time);

        track_movement = abs(cur_event->getTrack() - cur_track);
        total_movement += track_movement;

        eve_queue.push(new Event(cur_time + track_movement, cur_event->getTrack(), cur_event->getId(), FINISH));

        if(verbose){
          cout << cur_event->getTimestamp() << ":" << setw(6) << setfill(' ') 
            << cur_event->getId() << " issue " << cur_event->getTrack() << " " << cur_track << endl;
        }
        cur_track = cur_event->getTrack();

        break;
      case FINISH:
        req = io_requests[cur_event->getId()];
        req->setFinishTime(cur_time);

        if(verbose){
          cout << cur_event->getTimestamp() << ":" << setw(6) << setfill(' ') 
            << cur_event->getId() << " finish " << io_requests[cur_event->getId()]->getTotalTime() << endl;
        }

        break;
    }
    if(cur_time >= nextIOTime){
      IoRequest* req = absScheduler->get_next_track(cur_track);
      if(req == NULL){
        continue;
      }
      track_movement = abs(req->getTrackNumber() - cur_track);
      nextIOTime = cur_time + track_movement;
      eve_queue.push(new Event(cur_time, req->getTrackNumber(), req->getId(), ISSUE));
    }
  }

  unsigned int max_wait = 0;
  double average_turnaround_time = 0, average_wait_time = 0;
  if(verbose){
    cout << "IOREQS INFO" << endl;
  }
  for(int i = 0; i < io_requests.size(); i++){
    average_turnaround_time += io_requests[i]->getTotalTime();
    average_wait_time += io_requests[i]->getWaitTime();
    if(io_requests[i]->getWaitTime() > max_wait){
      max_wait = io_requests[i]->getWaitTime();
    }
    if(verbose){
      cout << *(io_requests[i]);
    }
  }

  average_turnaround_time /= io_requests.size();
  average_wait_time /= io_requests.size();

  printf("SUM: %d %d %.2lf %.2lf %d\n", cur_time, total_movement,
                  (double)average_turnaround_time, (double)average_wait_time,
                              max_wait);
}
