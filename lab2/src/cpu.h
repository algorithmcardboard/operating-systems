#include <fstream>
#include <string>
#include <iostream>
#include<stdlib.h>

#include <queue>
#include <vector>
#include <list>

#include "ds/processstate.h"
#include "ds/process.h"
#include "ds/processtable.h"
#include "ds/event.h"
#include "util/randomnumbergenerator.cpp"
#include "scheduler/fcfs.cpp"
#include "scheduler/lcfs.cpp"
#include "scheduler/sjf.cpp"
#include "scheduler/priority.cpp"
#include "scheduler/round_robin.cpp"

using namespace std;

class CPU{
  private:
    bool good;
    string error;
    ifstream *inFile, *randFile;
    RandomNumberGenerator* randGen;
    Scheduler* curScheduler;
    int quantum;
    bool verbose;

    struct EventComparator{
      bool operator()(const Event* event1, const Event* event2){
        if(event1->getTimestamp() != event2->getTimestamp()){
          return event1->getTimestamp() > event2->getTimestamp();
        }
        return event1->getSequenceNumber() > event2->getSequenceNumber();
      }
    };
    priority_queue<Event*, vector<Event*>, EventComparator> eventQueue;

    void populateEventQueue();

    Scheduler* getScheduler(char*);

  public:
    CPU(char*, char*, char*, bool);
    ~CPU();

    bool isGood();
    void start();
    string getError();
};
