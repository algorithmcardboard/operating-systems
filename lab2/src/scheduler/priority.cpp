#include "abstract_scheduler.h"

class PriorityScheduler : public Scheduler{
  public:
    PriorityScheduler():Scheduler(){}
    PriorityScheduler(int a):Scheduler(a){}

    void addProcess(Process* p){
      cout << "In add process flow";
    };

    Process* get_next_process(){
      return NULL;
    }
};
