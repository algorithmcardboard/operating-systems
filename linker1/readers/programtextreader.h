#ifndef PROGRAM_TEXT_READER_H
#define PROGRAM_TEXT_READER_H

#include <fstream>
#include <iostream>
#include "abstractreader.h"

using namespace std;

class ProgramTextReader : protected AbstractReader{
  public:
    ProgramTextReader(fstream& fin, long fs) : AbstractReader(fin, fs){
    };

    void doFirstPass(){
      char ch;
      *(this->fin) >> ch;
        cout << "PTR " << ch << "\n";
    };

    void doSecondPass(){
    }
};

#endif
