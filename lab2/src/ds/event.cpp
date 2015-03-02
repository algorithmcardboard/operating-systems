#include "event.h"

Event::Event(int timestamp, int pid, int oldState, int newState){
  timestamp = timestamp;
  pid = pid;
  oldState = oldState;
  newState = newState;
}
