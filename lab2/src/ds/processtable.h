#include <map>
#include "process.h"

using namespace std;

class ProcessTable{
  private:
    map<int, Process*>* table;
    static unsigned int globalPID;
    int totalIOTime;
    ProcessTable();


  public:
    static ProcessTable& getInstance();
    void push(Process*);
    Process* getProcess(int pid);

    void printPerProocessSummary();
    void printSummary();

    void setTotalIOUtil(int);
};
