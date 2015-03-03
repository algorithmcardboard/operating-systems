#include <iostream>
#include <stdlib.h>

#include "cpu.h"

using namespace std;

int main(int argc, char** argv){
  int c;

  bool verbose = false;

  char* schedulerSpec = NULL;
  char* inputFileName = NULL;
  char* randFileName = NULL;

  while((c = getopt(argc, argv, "vs:")) != -1){
    switch(c){
      case 'v':
        verbose = true;
        break;
      case 's':
        schedulerSpec = optarg;
        break;
      case '?':
        cout << "in question mark \n";
        break;
      default:
        cout << "exiting from the program";
        exit(99);
    }
  }

  if(argc - optind != 2){
    cout << "inputfile and randfile are required.\nInput the required inputs in the format specified. [-v] [-s<schedspec>] inputfile randfile\n";
    exit(99);
  }

  inputFileName = argv[optind];
  randFileName = argv[optind+1];

  CPU myCpu(inputFileName, randFileName);
  if(myCpu.isGood()){
    myCpu.start();
  }else{
    cout << myCpu.getError();
  }

  return 0;
}
