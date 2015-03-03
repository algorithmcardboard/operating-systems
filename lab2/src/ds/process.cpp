#include "process.h"

unsigned int Process::globalPID = 0;

Process::Process(int arrivalTime, int totalCPUTime, int cpuBurst, int ioBurst){
  this->pid = ++globalPID;
  this->arrivalTime = arrivalTime;
  this->totalCPUTime = totalCPUTime;
  this->cpuBurst = cpuBurst;
  this->ioBurst = ioBurst;
  this->currentState = CREATED;
}

int Process::getPID(){
  return pid;
}

ProcessState Process::getCurrentState(){
  return currentState;
}
