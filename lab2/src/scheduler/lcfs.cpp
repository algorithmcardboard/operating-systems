#include "abstract_scheduler.h"

class  LCFS : public Scheduler{

  public:
    LCFS():Scheduler(){}
    LCFS(int a):Scheduler(a){}

    void addProcess(Process* p){
      cout << "In add process flow";
    };

    Process* get_next_process(){
      return NULL;
    }
};
