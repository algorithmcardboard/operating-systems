#include <fstream>
#include <string>

using namespace std;

class CPU{
  private:
    bool good;
    string error;
    ifstream *inFile, *randFile;
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
  }
}

