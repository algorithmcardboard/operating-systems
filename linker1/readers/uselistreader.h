#ifndef USE_LIST_READER_H
#define USE_LIST_READER_H

#include <fstream>
#include <iostream>
#include "abstractreader.h"

using namespace std;

class UseListReader : protected AbstractReader{

  public:
    UseListReader(fstream& fin, long fs) : AbstractReader(fin, fs){
    };

    void doFirstPass(){
      char ch;
      *(this->fin) >> ch;
        cout << "ULR " << ch << "\n";
    };

    void doSecondPass(){
    }
};

#endif
