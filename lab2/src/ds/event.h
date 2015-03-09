#include<iostream>
#include<string>
#include"processstate.h"

using namespace std;

class Event{
  public:
    enum Transition{
      T_CREATE=1,
      T_RUN = 2,
      T_BLOCK = 3,
      T_UNBLOCK = 4,
      T_PREEMPT = 5,
      T_TERMINATE = 6
    };

    Event(int ts, int pid, ProcessState, ProcessState);
    int getTimestamp() const;
    int getSequenceNumber() const;
    int getPID() const;
    ProcessState getOldState() const;
    ProcessState getNewState() const;
    Transition getTransition() const;
    const char* getTransitionLogString();

    friend ostream& operator<< (ostream &out, Event &eve);

  private:
    static unsigned int sequence;

    int timestamp, seqNum, pid;

    ProcessState oldState, newState;
    Transition transition;
    Transition figureOutTransition();
    string getTransitionString(ProcessState);
};
