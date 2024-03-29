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
#include "pr_algos/second_chance.cpp"
#include "pr_algos/random.cpp"
#include "pr_algos/clock.cpp"
#include "pr_algos/aging.cpp"
#include "pr_algos/lru.cpp"
#include "pr_algos/nru.cpp"
#include "pr_algos/virtual_clock.cpp"
#include "pr_algos/virtual_aging.cpp"

using namespace std;

AbstractPR* getMMUAlgo(char* algoStr, ifstream& randFile, vector<pte>* pt, vector<unsigned int>* ft, vector<unsigned int>* ftop, int nf, int np){
  char c = algoStr[0];
  AbstractPR* algo = NULL;
  switch(c){
    case 'N':
      algo = new NRU(pt, ft, ftop, randFile);
      break;
    case 'X':
      algo = new VirtualClock(pt, ft, ftop);
      break;
    case 'Y':
      algo = new VirtualAging(pt, ft, ftop, np);
      break;
    case 'l':
      algo = new LRU(pt, ft, ftop);
      break;
    case 'r':
      algo = new Random(pt, ft, ftop, randFile);
      break;
    case 'f':
      algo = new FIFO(pt, ft, ftop);
      break;
    case 's':
      algo = new SecondChance(pt, ft, ftop);
      break;
    case 'c':
      algo = new Clock(pt, ft, ftop);
      break;
    case 'a':
      algo = new Aging(pt, ft, ftop, nf);
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

  AbstractPR* prAlgo = getMMUAlgo(mmuAlgoStr, *(randFile), page_table, frame_table, ftop, numFrames, 64);

  MMU mmu(page_table, frame_table, ftop, prAlgo, numFrames, options);

  char operation = 0; int pageNum = 0; string tmp;

  while(*(inFile) >> operation){
    if(operation == '#'){
      //cout << "Skipping the line as it is comment" << endl;
      getline(*(inFile), tmp);
      continue;
    }
    *(inFile) >> pageNum;
    mmu.executeOperation(operation, pageNum);
  }

  mmu.printPageTable();
  mmu.printFrameTable();
  mmu.printSummary();

  return 0;
}
