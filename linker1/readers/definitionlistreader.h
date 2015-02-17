#ifndef DEFINITION_LIST_READER_H
#define DEFINITION_LIST_READER_H

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "abstractreader.h"
#include "../ds/symbol.h"
#include "../ds/symboltable.h"

using namespace std;

class DefinitionListReader : protected AbstractReader{


  public:
    DefinitionListReader(fstream& fin, long fs) : AbstractReader(fin, fs){
    };

    int doFirstPass(int baseModuleLength, int moduleCount){
      Token<int> dlCount = getNextTokenAsInteger(true);
      int multipleDefinitionCount = 0;
      if(dlCount.getValue() > 16){
        cout << "Parse Error line "<<dlCount.getLineNumber() << " offset "<<dlCount.getColumnNumber()<< ": TO_MANY_DEF_IN_MODULE\n";
        exit(99);
      }

      for(int iterator = 0; iterator < dlCount.getValue(); iterator++){
        Symbol symbol = getSymbol();
        Token<int> symbolValue = getNextTokenAsInteger(false);

        symbol.setRelativeAddress(symbolValue.getValue());
        symbol.setModuleBaseAddress(baseModuleLength);
        symbol.setModuleCount(moduleCount);

        SymbolTable& instance = SymbolTable::getInstance();
        bool mulDefns = instance.push(symbol);
        if(mulDefns){
          multipleDefinitionCount++;
        }
      }
      return dlCount.getValue() - multipleDefinitionCount;
    };

    void doSecondPass(){
      Token<int> dlCount = getNextTokenAsInteger(true);
      for(int iterator = 0; iterator < dlCount.getValue(); iterator++){
        Symbol symbol = getSymbol();
        Token<int> symbolValue = getNextTokenAsInteger(false);
      }
    }
};

#endif
