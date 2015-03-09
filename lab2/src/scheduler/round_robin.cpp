#include "abstract_scheduler.h"

#include <queue>

using namespace std;

class RoundRobin : public Scheduler{
  private:
    queue<Process*> runQueue;
  public:
    RoundRobin():Scheduler(){}
    RoundRobin(int a):Scheduler(a){}

    void addProcess(Process* p){
      runQueue.push(p);
    };

    Process* get_next_process(){
      Process* p = runQueue.front();
      runQueue.pop();
      return p;
    }
};
