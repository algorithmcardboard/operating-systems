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
      if(dlCount.getValue() > 16){
        cout << "Parse Error line "<<dlCount.getLineNumber() << " offset "<<dlCount.getColumnNumber()<< ": TO_MANY_DEF_IN_MODULE\n";
        exit(99);
      }

      for(int iterator = 0; iterator < dlCount.getValue(); iterator++){
        Token<char*> symbol = getSymbol();
        Token<int> symbolValue = getNextTokenAsInteger();
      }
    };

    void doSecondPass(){
    }
};

#endif
