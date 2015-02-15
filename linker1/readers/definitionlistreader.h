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

    int doFirstPass(int baseModuleLength){
      Token<int> dlCount = getNextTokenAsInteger();
      if(dlCount.getValue() > 16){
        cout << "Parse Error line "<<dlCount.getLineNumber() << " offset "<<dlCount.getColumnNumber()<< ": TO_MANY_DEF_IN_MODULE\n";
        exit(99);
      }

      for(int iterator = 0; iterator < dlCount.getValue(); iterator++){
        Symbol symbol = getSymbol();
        Token<int> symbolValue = getNextTokenAsInteger();

        symbol.setRelativeAddress(symbolValue.getValue());
        symbol.setModuleBaseAddress(baseModuleLength);

        SymbolTable& instance = SymbolTable::getInstance();
        instance.push(symbol);
      }
      return dlCount.getValue();
    };

    void doSecondPass(){
    }
};

#endif
