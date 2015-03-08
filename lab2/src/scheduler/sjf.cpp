#include "abstract_scheduler.h"

class SJF : public Scheduler{
  public:
    SJF():Scheduler(){}
    SJF(int a):Scheduler(a){}

    void addProcess(Process* p){
      cout << "In add process flow";
    };

    Process* get_next_process(){
      return NULL;
    }
};
