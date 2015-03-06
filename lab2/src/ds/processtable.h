#include <map>
#include "process.h"

using namespace std;

class ProcessTable{
  private:
    map<int, Process>* table;
    static unsigned int globalPID;
    ProcessTable();

  public:
    static ProcessTable& getInstance();
    void push(Process*);
};
