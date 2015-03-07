#include "abstract_scheduler.h"

class PriorityScheduler : public Scheduler{
  public:
    PriorityScheduler():Scheduler(){}
    PriorityScheduler(int a):Scheduler(a){}
};
