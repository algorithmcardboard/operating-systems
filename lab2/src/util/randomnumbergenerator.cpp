#include<iostream>

using namespace std;

class RandomNumberGenerator{
  private:
    ifstream* randFile;
    int* seed;
    int size;
    int ofs;

    int myrandom(int burst) { 
      int val = 1 + (*(seed + (ofs % size)) % burst); 
      ofs = (ofs + 1) % size;
      return val;
    }
  public:
    RandomNumberGenerator(ifstream& fin){
      randFile = &(fin);
      *(randFile) >> size;
      seed = new int[size];
      for(int i = 0; i < size; i++){
        *(randFile) >> *(seed + i);
      }
      ofs = 0;
    }

    ~RandomNumberGenerator(){
      delete seed;
    }

    /*
    void printSeed(){
      cout << size << endl;
      for(int i = 0; i < size; i++){
        cout << *(seed + i) << endl;
      }
    }*/

    int getBurstCycle(int seedValue){
      return myrandom(seedValue);
    }

    int getStaticPriority(){
      return myrandom(4);
    }
};
