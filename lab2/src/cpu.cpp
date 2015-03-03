#include "cpu.h"

using namespace std;

// Destructor
CPU::~CPU(){
  inFile->close();
  randFile->close();
  delete inFile;
  delete randFile;
}

// Constructor 
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
    cout << *(eve);
    eventQueue.pop();
  }
}
