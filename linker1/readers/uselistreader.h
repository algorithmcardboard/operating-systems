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
      Token<int> ulCount = getNextTokenAsInteger(true);
      if(ulCount.getValue() > 16){
        cout << "Parse Error line "<<ulCount.getLineNumber() << " offset "<<ulCount.getColumnNumber()<< ": TO_MANY_USE_IN_MODULE\n";
        exit(99);
      }

      for(int iterator = 0; iterator < ulCount.getValue(); iterator++){
        Symbol symbol = getSymbol();
      }
    };

    void doSecondPass(){
    }
};

#endif
