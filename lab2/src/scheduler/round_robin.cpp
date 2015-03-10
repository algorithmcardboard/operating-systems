#include "abstract_scheduler.h"

#include <queue>

using namespace std;

class RoundRobin : public Scheduler{
  private:
    queue<Process*>* runQueue;
  public:
    RoundRobin():Scheduler(){
      runQueue = new queue<Process*>();
    }
    RoundRobin(int a):Scheduler(a){
      runQueue = new queue<Process*>();
    }

    void addProcess(Process* p){
      p->resetDynamicPriority();
      runQueue->push(p);
    };

    Process* get_next_process(){
      if(runQueue->size() <= 0){
        return NULL;
      }
      Process* p = runQueue->front();
      if(p != NULL){
        runQueue->pop();
      }
      return p;
    }
};
