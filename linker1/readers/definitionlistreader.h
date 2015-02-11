#ifndef DEFINITION_LIST_READER_H
#define DEFINITION_LIST_READER_H

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "abstractreader.h"

using namespace std;

class DefinitionListReader : protected AbstractReader{

  public:
    DefinitionListReader(fstream& fin) : AbstractReader(fin){
    };

    void doFirstPass(){
      Token<int> dlCount = getNextTokenAsInteger();
      for(int iterator = 0; iterator < dlCount.getValue(); iterator++){
        Token<char*> symbol = getNextToken();
        cout << "iterating once " << symbol.getValue() << " " << symbol.getLineNumber() << " " << symbol.getColumnNumber() << "\n";
        Token<int> symbolValue = getNextTokenAsInteger();
      }
    };

    void doSecondPass(){
    }
};

#endif
