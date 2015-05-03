#ifndef IOREQUEST_CPP
#define IOREQUEST_CPP

#include <iostream>
#include <iomanip>

using namespace std;

class IoRequest{
  private:
    unsigned int arrival_time;
    unsigned int track_number;
    unsigned int io_id;
    unsigned int finishTime;
    unsigned int issue_time;

    static unsigned int ioCounter;
  public:
    IoRequest(unsigned int arrivalTime, unsigned int trackNumber){
      arrival_time = arrivalTime;
      track_number = trackNumber;
      io_id = ioCounter++;
      finishTime = 0;
      issue_time = 0;
    }

    unsigned int getId(){
      return io_id;
    }

    unsigned int getArrivalTime(){
      return arrival_time;
    }

    unsigned int getTrackNumber(){
      return track_number;
    }

    void setFinishTime(unsigned int ft){
      finishTime = ft;
    }

    void setIssueTime(unsigned int it){
      issue_time = it;
    }

    unsigned int getTotalTime(){
      return finishTime - arrival_time;
    }

    unsigned int getWaitTime(){
      return issue_time - arrival_time;
    }

    friend ostream& operator<< (ostream &out, IoRequest &ior){
      out << setw(5) << setfill(' ') <<  ior.io_id << ":" 
        << setw(6) << setfill(' ') << ior.arrival_time 
        << setw(6) << setfill(' ') << ior.issue_time 
        << setw(6) << setfill(' ') << ior.finishTime << endl;
    }
};

unsigned int IoRequest::ioCounter = 0;

#endif
