#include "abstract_scheduler.h"
#include <sstream>

#include <queue>

using namespace std;

class RoundRobin : public Scheduler{
  private:
    queue<Process*>* runQueue;
    string name;
  public:
    RoundRobin():Scheduler(){
      runQueue = new queue<Process*>();
      name = "RR";
    }

    RoundRobin(int a):Scheduler(a){
      runQueue = new queue<Process*>();
      stringstream s;
      s << "RR " << quantum;
      name = s.str();
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
      return name;
    }
};
