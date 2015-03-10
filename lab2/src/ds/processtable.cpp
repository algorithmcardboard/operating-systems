#include "processtable.h" 
#include <iostream>

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
