#include "abstract_scheduler.h"

class FCFS : public Scheduler{
  public:
    FCFS():Scheduler(){}
    FCFS(int a):Scheduler(a){}

    void addProcess(Process* p){
      cout << "In add process flow";
    };

    Process* get_next_process(){
      return NULL;
    }
};
