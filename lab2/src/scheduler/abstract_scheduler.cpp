#include "abstract_scheduler.h"

#include "fcfs.cpp"
#include "lcfs.cpp"
#include "sjf.cpp"
#include "priority.cpp"
#include "round_robin.cpp"

using namespace std;

Scheduler::Scheduler(){
}

Scheduler::Scheduler(int quantum){
  this->quantum = quantum;
}
