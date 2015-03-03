#include <fstream>
#include <string>
#include <iostream>

#include <queue>
#include <vector>

#include "ds/processstate.h"
#include "ds/process.h"
#include "ds/processtable.h"
#include "ds/event.h"

using namespace std;

class CPU{
  private:
    bool good;
    string error;
    ifstream *inFile, *randFile;

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

  public:
    CPU(char*, char* );
    ~CPU();

    bool isGood();
    void start();
    string getError();
};
