#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

char* getMMUAlgo(char* algoStr, ifstream& fin){
  char c = algoStr[0];
  char* algo = NULL;
  switch(c){
    case 'N':
      // NRU (four classes)
      // based on virtual pages
      algo = (char*)"NRU (VP)";
      break;
    case 'X':
      // Clock
      // based on virtual pages
      algo = (char*)"Clock (VP)";
      break;
    case 'Y':
      // Aging
      // based on virtual pages
      algo = (char*)"Aging (VP)";
      break;
    case 'l':
      // LRU (Least Reently used)
      // based on physical frames
      algo = (char*)"LRU (PF)";
      break;
    case 'r':
      // Random 
      // based on physical frames
      algo = (char*)"Random (PF)";
      break;
    case 'f':
      // FIFO
      // based on physical frames
      algo = (char*)"FIFO (PF)";
      break;
    case 's':
      // Second chance
      // based on physical frames
      algo = (char*)"Second Chance (PF)";
      break;
    case 'c':
      // Clock
      // based on physical frames
      algo = (char*)"Clock (PF)";
      break;
    case 'a':
      // Aging
      // based on physical frames
      algo = (char*)"Aging (PF)";
      break;
    default:
      algo = NULL;
  }
  return algo;
}

int main(int argc, char** argv){
  int c;
  char* mmuAlgoStr = NULL;
  char* frameNum = NULL;
  char* options = NULL;
  char* inputFileName = NULL;
  char* randFileName = NULL;
  int numFrames = 32;

  ifstream *inFile, *randFile;

  while((c = getopt(argc, argv, "a:o:f:")) != -1){
    switch(c){
      case 'a':
        mmuAlgoStr = optarg;
        break;
      case 'o':
        options = optarg;
        break;
      case 'f':
        numFrames = atoi(optarg);
        break;
    }
  }

  if(numFrames <= 0){
    numFrames = 32;
  }

  if(argc - optind != 2){
    cout << "Input file & rand file are required.  Exiting" << endl;
    exit(99);
  }

  inputFileName = argv[optind];
  randFileName = argv[optind+1];

  inFile = new ifstream(inputFileName);
  randFile = new ifstream(randFileName);

  if(!inFile->good()){
    cout << "Invalid input file" << endl;;
    exit(99);
  }

  if(!randFile->good()){
    cout << "Invalid rand file" << endl;
    exit(99);
  }

  getMMUAlgo(mmuAlgoStr, *(randFile));

  cout << "Options are " << mmuAlgoStr << " " << options << " " << numFrames << " " << inputFileName << " " << randFileName << endl;
  return 0;
}
