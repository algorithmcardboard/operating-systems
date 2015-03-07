#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <limits.h>
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
};

#endif
