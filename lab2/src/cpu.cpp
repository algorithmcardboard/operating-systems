#include <fstream>
#include <string>

#include <queue>
#include <vector>

#include "ds/process.h"
#include "ds/event.h"

using namespace std;

class CPU{
  private:
    bool good;
    string error;
    ifstream *inFile, *randFile;

    struct EventComparator{
      bool operator()(const Event* event1, const Event* event2){
        return event1->getTimestamp() > event2->getTimestamp();
      }
    };
    priority_queue<Event*, vector<Event*>, EventComparator> eventQueue;
  public:
    CPU(char*, char* );
    ~CPU();

    bool isGood();
    void start();
    string getError();
};


CPU::CPU(char* inputFileName, char* randFileName){
  good = true;
  inFile = new ifstream(inputFileName);
  randFile = new ifstream(randFileName);

  if(!inFile->good()){
    good = false;
    error += "Invalid input file\n";
  }

  if(!randFile->good()){
    good = false;
    error += "Invalid rand file\n";
  }
}

CPU::~CPU(){
  inFile->close();
  randFile->close();
  delete inFile;
  delete randFile;
}

bool CPU::isGood(){
  return good;
}

string CPU::getError(){
  return error;
}

void CPU::start(){
  int arrivalTime, totalCPU, cpuBurst, ioBurst;
  while(*(inFile) >> arrivalTime >> totalCPU >> cpuBurst >> ioBurst){
    Process* newProcess = new Process(arrivalTime, totalCPU, cpuBurst, ioBurst);
    Event* eve = new Event(arrivalTime, newProcess->getPID(), 2, 3);
    eventQueue.push(eve);
  }
  while(!eventQueue.empty()){
    Event* eve = eventQueue.top();
    cout << "Popping an event" << eve->getTimestamp();
    eventQueue.pop();
  }
}
