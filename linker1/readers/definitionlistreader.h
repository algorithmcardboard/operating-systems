#ifndef DEFINITION_LIST_READER_H
#define DEFINITION_LIST_READER_H

#include <fstream>
#include <iostream>
#include "abstractreader.h"

using namespace std;

class DefinitionListReader : protected AbstractReader{
  private:
    fstream* fin;

  public:
    DefinitionListReader(fstream& fin){
      this->fin = &(fin);
    };

    void doFirstPass(){
      char ch;
      *(this->fin) >> ch;
        cout << "DLR " << ch << "\n";
    };
};

#endif
