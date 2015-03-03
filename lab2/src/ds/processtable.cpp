#include "processtable.h" 

ProcessTable& ProcessTable::getInstance(){
  static ProcessTable instance;
  return instance;
}

ProcessTable::ProcessTable(){ 
  this->table = new map<int, Process>();
}
