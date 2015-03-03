#include "event.h"
#include <iostream>

using namespace std;

Event::Event(int timestamp, int pid, int oldState, int newState){
  cout << "setting timestamp to "<< timestamp<< endl;
  this->timestamp = timestamp;
  this->pid = pid;
  this->oldState = oldState;
  this->newState = newState;
}

int Event::getTimestamp() const{
  return timestamp;
}
