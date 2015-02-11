#ifndef DEFINITION_LIST_READER_H
#define DEFINITION_LIST_READER_H

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "abstractreader.h"

using namespace std;

class DefinitionListReader : protected AbstractReader{

  private:
    unsigned int getTokenAsInteger(){
      char *last = 0;
      Token<char*> token = getNextToken();
      int intVal = (int) strtol(token.getValue(), &last, 10);
      if(*last != 0){
        return -1;
      }
      return intVal;
    }

  public:
    DefinitionListReader(fstream& fin) : AbstractReader(fin){
    };

    void doFirstPass(){
      int count = getTokenAsInteger();
      if(count < 0){
        cout << "Expected integer. Got string. Terminating";
      }else{
        cout << "Got integer. Value is " << count << "\n";
      }
    };

    void doSecondPass(){
    }
};

#endif
