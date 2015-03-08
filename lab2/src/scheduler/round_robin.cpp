#include "abstract_scheduler.h"

using namespace std;

class RoundRobin : public Scheduler{
  public:
    RoundRobin():Scheduler(){}
    RoundRobin(int a):Scheduler(a){}

    void addProcess(Process* p){
      cout << "In add process flow";
    };

    Process* get_next_process(){
      return NULL;
    }
};
