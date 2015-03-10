#include "processtable.h" 
#include <iostream>
#include <iomanip>

using namespace std;

ProcessTable& ProcessTable::getInstance(){
  static ProcessTable instance;
  return instance;
}

ProcessTable::ProcessTable(){ 
  this->table = new map<int, Process*>();
}

void ProcessTable::push(Process* newProcess){
  table->insert(pair<int, Process*>(newProcess->getPID(), newProcess));
}

Process* ProcessTable::getProcess(int pid){
  return table->at(pid);
}

void ProcessTable::printPerProocessSummary(){
  for(map<int, Process*>::iterator ci = table->begin(); ci != table->end(); ci++){
    Process* p = ci->second;
    cout << setfill('0') << setw(4) << ci->first << ":";
    cout << setfill(' ') << setw(4) << p->getArrivalTime();
    cout << " " << setfill(' ') << setw(4) << p->getTotalCPUTime();
    cout << " " << setfill(' ') << setw(4) << p->getCpuBurst();
    cout << " " << setfill(' ') << setw(4) << p->getIOBurst();
    cout << " " << p->getStaticPriority();
    cout << " | ";
    cout << setfill(' ') << setw(5) << p->getLastTransitionTime() << " ";
    cout << setfill(' ') << setw(5) << p->getTurnaroundTime() << " ";
    cout << setfill(' ') << setw(5) << p->getIOTime() << " ";
    cout << setfill(' ') << setw(5) << p->getCpuWaitingTime();
    cout << endl;
  }
}

void ProcessTable::printSummary(){
}
