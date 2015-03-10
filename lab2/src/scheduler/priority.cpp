#include "abstract_scheduler.h"
#include <sstream>

using namespace std;

class PriorityScheduler : public Scheduler{
  private:
    string name;
  public:
    PriorityScheduler():Scheduler(){}
    PriorityScheduler(int a):Scheduler(a){
      stringstream s;
      s << "PRIO " << quantum;
      name = s.str();
    }

    void addProcess(Process* p){
      cout << "In add process flow";
    };

    Process* get_next_process(){
      return NULL;
    }

    string getName(){
      return name;
    }
};
