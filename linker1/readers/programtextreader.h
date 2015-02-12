#ifndef PROGRAM_TEXT_READER_H
#define PROGRAM_TEXT_READER_H

#include <fstream>
#include <iostream>
#include "abstractreader.h"

using namespace std;

class ProgramTextReader : protected AbstractReader{
  private:
    static const int TOTAL_ADDRESSABLE_MEMORY = 512;
    int availableMemory;

    Token<char> getAddressType(){
      Token<char*> addressType = getNextToken();
      if(addressType.getLength() != 1){
        cout << "Parse Error line "<< addressType.getLineNumber() << " offset "<<addressType.getColumnNumber()<< ": ADDR_EXPECTED\n";
        exit(99);
      }
      char ch = addressType.getValue()[0];
      if(! (ch == 'I' || ch == 'A' || ch == 'E' || ch == 'R') ){
        cout << "Parse Error line "<< addressType.getLineNumber() << " offset "<<addressType.getColumnNumber()<< ": ADDR_EXPECTED\n";
        exit(99);
      }
    };

  public:
    ProgramTextReader(fstream& fin, long fs) : AbstractReader(fin, fs){
      this->availableMemory = TOTAL_ADDRESSABLE_MEMORY;
    };

    void doFirstPass(){
      Token<int> prCount = getNextTokenAsInteger();
      this->availableMemory -= prCount.getValue();
      if(this->availableMemory < 0){
        cout << "Parse Error line "<<prCount.getLineNumber() << " offset "<<prCount.getColumnNumber()<< ": TO_MANY_INSTR\n";
        exit(99);
      }
      int iterator = 0;
      for(int iterator = 0; iterator < prCount.getValue(); iterator++){
        Token<char> addr = getAddressType();
        Token<char*> instruction = getNextToken();
      } 
    };

    void doSecondPass(){
    }
};

#endif
