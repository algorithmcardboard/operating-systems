#include "abstract_scheduler.h"
#include <queue>

class SJF : public Scheduler{
  private:
    struct ProcessComparator{
      bool operator()(Process* p1, Process* p2){
        if(p1->getRemainingTime() != p2->getRemainingTime()){
          return p1->getRemainingTime() > p2->getRemainingTime();
        }
        if(p1->getLastTransitionTime() != p2->getLastTransitionTime()){
          return p1->getLastTransitionTime() > p2->getLastTransitionTime();
        }
        return p1->getPID() > p2->getPID();
      }
    };
    priority_queue<Process*, vector<Process*>, ProcessComparator> runQueue;
  public:
    SJF():Scheduler(){
    }
    SJF(int a):Scheduler(a){
    }

    void addProcess(Process* p){
      if(p != NULL){
        runQueue.push(p);
      }
    };

    Process* get_next_process(){
      if(runQueue.empty()){
        return NULL;
      }
      Process* p = runQueue.top();
      runQueue.pop();
      return p;
    }

    string getName(){
      return "SJF";
    }
};
