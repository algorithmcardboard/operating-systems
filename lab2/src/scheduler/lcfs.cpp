#include "abstract_scheduler.h"

#include <stack>

class LCFS : public Scheduler{
  private:
    stack<Process*>* runQueue;
  public:
    LCFS():Scheduler(){
      runQueue = new stack<Process*>();
    }
    LCFS(int a):Scheduler(a){
      runQueue = new stack<Process*>();
    }

    void addProcess(Process* p){
      p->resetDynamicPriority();
      runQueue->push(p);
    };

    Process* get_next_process(){
      if(runQueue->size() <= 0){
        return NULL;
      }
      Process* p = runQueue->top();
      if(p != NULL){
        runQueue->pop();
      }
      return p;
    }

    string getName(){
      return "FCFS";
    }
};
