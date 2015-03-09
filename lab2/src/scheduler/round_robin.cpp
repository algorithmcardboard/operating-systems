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
      runQueue->push(p);
    };

    Process* get_next_process(){
      Process* p = runQueue->front();
      runQueue->pop();
      return p;
    }
};
