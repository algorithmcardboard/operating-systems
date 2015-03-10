#include "abstract_scheduler.h"
#include <sstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class PriorityScheduler : public Scheduler{
  private:
    string name;
    queue<Process*>* activeQueue; 
    queue<Process*>* expiredQueue;

    Process* fetchFromQueue(queue<Process*>* q){
      Process* p = NULL;
      for(int i = 3; i >= 0; i--){
        if(q[i].size() == 0){
          continue;
        }
        p = q[i].front();
        q[i].pop();
        break;
      }
      return p;
    }
  public:
    PriorityScheduler():Scheduler(){}
    PriorityScheduler(int a):Scheduler(a){
      stringstream s;
      s << "PRIO " << quantum;
      name = s.str();

      activeQueue = new queue<Process*>[4];
      expiredQueue = new queue<Process*>[4];
    }

    void addProcess(Process* p){
      int dp = p->getDynamicPriority();

      queue<Process*>* queueToAdd = activeQueue; 

      if(dp < 0){
        queueToAdd = expiredQueue;
        p->resetDynamicPriority();
      }

      queueToAdd[p->getDynamicPriority()].push(p);
    };

    Process* get_next_process(){

      Process* p = fetchFromQueue(activeQueue);

      if(p == NULL){
        queue<Process*>* temp = activeQueue; 
        activeQueue  = expiredQueue;
        expiredQueue = temp;
        p = fetchFromQueue(activeQueue);
      }
      return p;
    }

    string getName(){
      return name;
    }
};
