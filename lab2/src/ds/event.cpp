#include "event.h"

using namespace std;

unsigned int Event::sequence= 0;

Event::Transition Event::figureOutTransition(){
  if(oldState == CREATED && newState == READY){
    transition  = T_CREATE;
  }else if(oldState == READY && newState == RUNNING){
    transition = T_RUN;
  }else if(oldState == RUNNING){
    if(newState == BLOCKED){
      transition = T_BLOCK;
    }else if(newState == READY){
      transition = T_PREEMPT;
    }
  }else if(oldState == BLOCKED && newState == READY){
    transition = T_UNBLOCK;
  }
  return transition;
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

string Event::getTransitionString(ProcessState state){
  string stateStr = "";
  switch(state){
    case CREATED:
      stateStr += "CREATED";
      break;
    case READY:
      stateStr += "READY";
      break;
    case RUNNING:
      stateStr += "RUNNG";
      break;
    case BLOCKED:
      stateStr += "BLOCK";
      break;
  }
  return stateStr;
}

const char* Event::getTransitionLogString(){
  return string(getTransitionString(oldState) + " -> " + getTransitionString(newState)).c_str();
}

ostream& operator<< (ostream &out, Event &eve){
  out << "Event[Timestamp: "<< eve.timestamp<<" PID: "<< eve.pid<< " OldState: "<< eve.oldState<<" NewState: "<< eve.newState<< " Sequence: "<< eve.seqNum << " Transition: "<< eve.getTransitionLogString() <<" ]" << endl;
}

Event::Transition Event::getTransition() const{
  return this->transition;
}
