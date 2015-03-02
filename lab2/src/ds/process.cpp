#include "process.h"

unsigned int Process::globalPID = 0;

Process::Process(int arrivalTime, int totalCPUTime, int cpuBurst, int ioBurst){
  pid = globalPID++;
  arrivalTime = arrivalTime;
  totalCPUTime = totalCPUTime;
  cpuBurst = cpuBurst;
  ioBurst = ioBurst;
}

int Process::getPID(){
  return pid;
}
