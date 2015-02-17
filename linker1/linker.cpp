#include <iostream>
#include <fstream>
#include <list>

#include "readers/objectmodulereader.h"
#include "ds/symboltable.h"

using namespace std;

int main(int argc, char* argv[]){
  if(argc != 2){
    cout << "Expected argument after options\n";
  }
  ObjectModuleReader* reader = new ObjectModuleReader(argv[1]);
  reader->doFirstPass();
  reader->firstPassCleanup();
  reader->doSecondPass();
  SymbolTable& instance = SymbolTable::getInstance();
  instance.printUnusedSymbols();
}
