#ifndef USE_LIST_READER_H
#define USE_LIST_READER_H

#include <fstream>
#include <iostream>
#include "abstractreader.h"

using namespace std;

class UseListReader : protected AbstractReader{
  private:
    fstream* fin;

  public:
    UseListReader(fstream& fin){
      this->fin = &(fin);
    };

    void doFirstPass(){
      char ch;
      *(this->fin) >> ch;
        cout << "ULR " << ch << "\n";
    };
};

#endif
