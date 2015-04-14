#include <iostream>
#include <stdlib.h>

char* getMMUAlgo(char* algoStr){
  return (char*)"asdf";
}

int main(int argc, char** argv){
  int c;
  char* mmuAlgo = NULL;
  char* frameNum = NULL;
  char* inputFileName = NULL;
  char* randFileName = NULL;
  int numFrames = 32;
  while((c = getopt(argc, argv, "a:o:f:")) != -1){
    switch(c){
      case 'a':
        mmuAlgo = getMMUAlgo(optarg);
        break;
      case 'o':
        break;
      case 'f':
        frameNum = optarg;
        numFrames = atoi(frameNum);
        break;
    }
  }

  if(numFrames <= 0){
    numFrames = 32;
  }

  if(argc - optind != 2){
  }

  inputFileName = argv[optind];
  randFileName = argv[optind+1];
  return 0;
}
