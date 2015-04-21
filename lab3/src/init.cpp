#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <list>

#include "ds/pte.h"
#include "mmu.cpp"
#include "pr_algos/abstract_pr.cpp"
#include "pr_algos/fifo.cpp"

using namespace std;

AbstractPR* getMMUAlgo(char* algoStr, ifstream& fin, vector<pte>* pt, vector<unsigned int>* ft, vector<unsigned int>* ftop){
  char c = algoStr[0];
  AbstractPR* algo = NULL;
  switch(c){
    case 'N':
      // NRU (four classes)
      // based on virtual pages
      //algo = (char*)"NRU (VP)";
      break;
    case 'X':
      // Clock
      // based on virtual pages
      //algo = (char*)"Clock (VP)";
      break;
    case 'Y':
      // Aging
      // based on virtual pages
      //algo = (char*)"Aging (VP)";
      break;
    case 'l':
      // LRU (Least Reently used)
      // based on physical frames
      //algo = (char*)"LRU (PF)";
      break;
    case 'r':
      // Random 
      // based on physical frames
      //algo = (char*)"Random (PF)";
      break;
    case 'f':
      // FIFO
      // based on physical frames
      algo = new FIFO(pt, ft, ftop);
      break;
    case 's':
      // Second chance
      // based on physical frames
      //algo = (char*)"Second Chance (PF)";
      break;
    case 'c':
      // Clock
      // based on physical frames
      //algo = (char*)"Clock (PF)";
      break;
    case 'a':
      // Aging
      // based on physical frames
      //algo = (char*)"Aging (PF)";
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

  vector<pte>* page_table = new vector<pte>();

  static const struct pte EMPTY_PTE = {0, 0, 0, 0, 0};

  for(int i = 0; i < 64; i++){
    page_table->push_back(EMPTY_PTE);
  }

  vector<unsigned int>* frame_table;
  vector<unsigned int>* ftop;

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

  frame_table = new vector<unsigned int>();
  ftop = new vector<unsigned int>();

  for(int i = 0; i < numFrames; i++){
    ftop->push_back(-1);
  }

  AbstractPR* prAlgo = getMMUAlgo(mmuAlgoStr, *(randFile), page_table, frame_table, ftop);

  MMU mmu(page_table, frame_table, ftop, prAlgo, numFrames, options);

  char operation = 0; int pageNum = 0; string tmp;

  while(*(inFile) >> operation >> pageNum){
    if(operation == '#'){
      //cout << "Skipping the line as it is comment" << endl;
      getline(*(inFile), tmp);
      continue;
    }
    mmu.executeOperation(operation, pageNum);
  }

  mmu.printPageTable();
  mmu.printFrameTable();
  mmu.printSummary();

  return 0;
}
