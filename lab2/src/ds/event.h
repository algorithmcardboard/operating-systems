#include<iostream>
#include"processstate.h"

using namespace std;

class Event{
  public:
    enum Transition{
      T_CREATE=1,
      T_RUN,
      T_BLOCK,
      T_UNBLOCK,
      T_PREEMPT,
      T_TERMINATE
    };

    Event(int, int, ProcessState, ProcessState);
    int getTimestamp() const;
    int getSequenceNumber() const;
    int getPID() const;
    ProcessState getOldState() const;
    ProcessState getNewState() const;
    Transition getTransition() const;

    friend ostream& operator<< (ostream &out, Event &eve);

  private:
    static unsigned int sequence;
    int timestamp, seqNum, pid;
    ProcessState oldState, newState;
    Transition transition;
    Transition figureOutTransition();
};
