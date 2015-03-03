#include<iostream>
#include"processstate.h"

using namespace std;

enum ProcessState;

class Event{
  private:
    static unsigned int sequence;
    int timestamp, seqNum, pid;
    ProcessState oldState, newState;

  public:
    Event(int, int, ProcessState, ProcessState);
    int getTimestamp() const;
    int getSequenceNumber() const;
    int getPID() const;
    ProcessState getOldState() const;
    ProcessState getNewState() const;
    friend ostream& operator<< (ostream &out, Event &eve);
};
