#include "processtable.h" 

ProcessTable& ProcessTable::getInstance(){
  static ProcessTable instance;
  return instance;
}

ProcessTable::ProcessTable(){ 
  table = new map<int, Process>();
}
