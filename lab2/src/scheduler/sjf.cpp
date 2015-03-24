#include "abstract_scheduler.h"
#include <queue>

class SJF : public Scheduler{
  private:
    unsigned int lastScheduledID;
    struct ProcessComparator{
      bool operator()(Process* p1, Process* p2){
        if(p1->getRemainingTime() != p2->getRemainingTime()){
          return p1->getRemainingTime() > p2->getRemainingTime();
        }
        if(p1->getLastTransitionTime() != p2->getLastTransitionTime()){
          return p1->getLastTransitionTime() > p2->getLastTransitionTime();
        }
        return p1->getLastScheduledId() > p2->getLastScheduledId();
      }
    };
    priority_queue<Process*, vector<Process*>, ProcessComparator> runQueue;
  public:
    SJF():Scheduler(){
      lastScheduledID = 0;
    }
    SJF(int a):Scheduler(a){
      lastScheduledID = 0;
    }

    void addProcess(Process* p){
      if(p != NULL){
        p->setLastScheduledId(lastScheduledID++);
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
