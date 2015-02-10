#ifndef PROGRAM_TEXT_READER_H
#define PROGRAM_TEXT_READER_H

#include <fstream>
#include <iostream>
#include "abstractreader.h"

using namespace std;

class ProgramTextReader : protected AbstractReader{
  private:
    fstream* fin;

  public:
    ProgramTextReader(fstream& fin){
      this->fin = &(fin);
    };

    void doFirstPass(){
      char ch;
      *(this->fin) >> ch;
        cout << "PTR " << ch << "\n";
    };
};

#endif
