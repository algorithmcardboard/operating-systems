#ifndef PROCESS_H
#define PROCESS_H

#include "processstate.h"

using namespace std;

class Process{
  private:
    static unsigned int globalPID;
    int arrivalTime, totalCPUTime, cpuBurst, ioBurst, pid, static_priority, dynamic_priority;
    ProcessState currentState;
    int remainingCPUBurst, remainingTime, lastTransitionTime;

  public:
    Process(int arrivalTime, int totalCPUTime, int cpuBurst, int ioBurst, int static_priority);
    int getPID();
    ProcessState getCurrentState();
    bool hasRemainingCPU();
    int getCpuBurst();
    int getIOBurst();
    int getRemainingCpuBurst();
    int getRemainingTime();
    void reduceRemainingTime(int);
    void setRemainingCpuBurst(int);
    void reduceDynamicPriority();
    void resetDynamicPriority();
    int getDynamicPriority();

    int getLastTransitionTime();
    void setLastTransitionTime(int);
};

#endif
