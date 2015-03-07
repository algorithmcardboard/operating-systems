#include "abstract_scheduler.h"

class RoundRobin : public Scheduler{
  public:
    RoundRobin():Scheduler(){}
    RoundRobin(int a):Scheduler(a){}
};
