#ifndef DEFINITION_LIST_READER_H
#define DEFINITION_LIST_READER_H

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "abstractreader.h"

using namespace std;

class DefinitionListReader : protected AbstractReader{

  public:
    DefinitionListReader(fstream& fin, long fs) : AbstractReader(fin, fs){
    };

    void doFirstPass(){
      Token<int> dlCount = getNextTokenAsInteger();

      for(int iterator = 0; iterator < dlCount.getValue(); iterator++){
        Token<char*> symbol = getNextToken();

        if(symbol.getLength() == 0){
          cout << "Parse Error line "<< symbol.getLineNumber() << " offset " << symbol.getColumnNumber()<< ": SYM_EXPECTED\n";
          exit(99);
        }
        Token<int> symbolValue = getNextTokenAsInteger();
      }
    };

    void doSecondPass(){
    }
};

#endif
