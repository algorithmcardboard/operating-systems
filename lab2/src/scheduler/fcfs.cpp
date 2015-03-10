#include "abstract_scheduler.h"

#include <queue>

class FCFS : public Scheduler{
  private:
    queue<Process*>* runQueue;
  public:
    FCFS():Scheduler(){
      runQueue = new queue<Process*>();
    }
    FCFS(int a):Scheduler(a){
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

    string getName(){
      return "FCFS";
    }
};
