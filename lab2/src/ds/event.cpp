#include "event.h"

using namespace std;

unsigned int Event::sequence= 0;

Event::Event(int timestamp, int pid, int oldState, int newState){
  this->timestamp = timestamp;
  this->pid = pid;
  this->oldState = oldState;
  this->newState = newState;
  this->seqNum= ++sequence;
}

int Event::getTimestamp() const{
  return timestamp;
}

int Event::getSequenceNumber() const{
  return seqNum;
}

ostream& operator<< (ostream &out, Event &eve){
  out << "Event[Timestamp: "<< eve.timestamp<<" PID: "<< eve.pid<< " OldState: "<< eve.oldState<<" NewState: "<< eve.newState<< " Sequence: "<< eve.seqNum<<" ]" << endl;
}
