#include "event.h"

using namespace std;

unsigned int Event::sequence= 0;

Event::Transition Event::figureOutTransition(){
}

Event::Event(int timestamp, int pid, ProcessState oldState, ProcessState newState){
  this->timestamp = timestamp;
  this->pid = pid;
  this->oldState = oldState;
  this->newState = newState;
  this->seqNum= ++sequence;
  this->transition = figureOutTransition();
}

int Event::getTimestamp() const{
  return timestamp;
}

int Event::getSequenceNumber() const{
  return seqNum;
}

int Event::getPID() const{
  return pid;
}

ProcessState Event::getNewState() const{
  return newState;
}

ProcessState Event::getOldState() const{
  return oldState;
}

ostream& operator<< (ostream &out, Event &eve){
  out << "Event[Timestamp: "<< eve.timestamp<<" PID: "<< eve.pid<< " OldState: "<< eve.oldState<<" NewState: "<< eve.newState<< " Sequence: "<< eve.seqNum<<" ]" << endl;
}

Event::Transition Event::getTransition() const{
  return transition;
}
