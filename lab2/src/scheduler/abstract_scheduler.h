#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <limits.h>
#include "../ds/process.h"
#include <iostream>

using namespace std;

class Scheduler{
  private:
    int quantum;
  public:
    Scheduler(){
      quantum = INT_MAX;
    }

    Scheduler(int quantum){
      this->quantum = quantum;
    }

    int getQuantum(){
      return quantum;
    }

    virtual void addProcess(Process*) = 0;
    virtual Process* get_next_process() = 0;
};

#endif
