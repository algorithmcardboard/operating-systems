#ifndef PROCESS_H
#define PROCESS_H

#include "processstate.h"

using namespace std;

class Process{
  private:
    static unsigned int globalPID;
    int arrivalTime, totalCPUTime, cpuBurst, ioBurst, pid, static_priority;
    ProcessState currentState;
    int remainingTime;

  public:
    Process(int arrivalTime, int totalCPUTime, int cpuBurst, int ioBurst, int static_priority);
    int getPID();
    ProcessState getCurrentState();
};

#endif
