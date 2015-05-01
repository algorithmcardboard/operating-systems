#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "schedulers/abstract_scheduler.cpp"
#include "schedulers/fifo.cpp"
#include "schedulers/sstf.cpp"
#include "schedulers/scan.cpp"
#include "schedulers/cscan.cpp"
#include "schedulers/fscan.cpp"

using namespace std;

AbstractScheduler* getAlgorithm(char algoChar){
  AbstractScheduler* algo;
  /*
  switch(algoChar){
    case 'i':
      algo = new FIFO();
      break;
    case 'j':
      algo = new SSTF();
      break;
    case 's':
      algo = new SCAN();
      break;
    case 'c':
      algo = new CSCAN();
      break;
    case 'f':
      algo = new FSCAN();
      break;
  }*/
  return algo;
}

int main(int argc, char** argv){
  bool verbose = false, fscan = false, request_details = false;
  char c;
  while((c = getopt(argc, argv, "s:vfd:")) != -1){
    switch(c){
      case 's':
        break;
      case 'v':
        verbose = true;
        break;
      case 'f':
        fscan = true;
        break;
      case 'd':
        request_details = true;
        break;
    }
  }
}
