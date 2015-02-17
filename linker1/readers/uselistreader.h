#ifndef USE_LIST_READER_H
#define USE_LIST_READER_H

#include <fstream>
#include <map>
#include <iostream>
#include "abstractreader.h"
#include "../ds/uselist.h"

using namespace std;

class UseListReader : protected AbstractReader{

  public:
    UseListReader(fstream& fin, long fs) : AbstractReader(fin, fs){
    };

    void doFirstPass(){
      Token<int> ulCount = getNextTokenAsInteger(false);
      if(ulCount.getValue() > 16){
        cout << "Parse Error line "<<ulCount.getLineNumber() << " offset "<<ulCount.getColumnNumber()<< ": TO_MANY_USE_IN_MODULE\n";
        exit(99);
      }

      for(int iterator = 0; iterator < ulCount.getValue(); iterator++){
        Symbol symbol = getSymbol();
      }
    };

    map<int, UseList>* doSecondPass(){

      map<int,UseList>* useList= new map<int, UseList>();

      Token<int> ulCount = getNextTokenAsInteger(false);

      for(int iterator=0; iterator < ulCount.getValue(); iterator++){
        Symbol* symbol = new Symbol(getSymbol());
        useList->insert(pair<int, UseList>(iterator, UseList(symbol)));
      }
      return useList;
    }
};

#endif
