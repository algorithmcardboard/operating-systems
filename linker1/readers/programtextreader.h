#ifndef PROGRAM_TEXT_READER_H
#define PROGRAM_TEXT_READER_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include "abstractreader.h"

using namespace std;

class ProgramTextReader : protected AbstractReader{
  private:
    static const int TOTAL_ADDRESSABLE_MEMORY = 512;
    int availableMemory;

    Token<char> getAddressType(){
      Token<char*> addressType = getNextToken(false);
      if(addressType.getLength() != 1){
        cout << "Parse Error line "<< addressType.getLineNumber() << " offset "<<addressType.getColumnNumber()<< ": ADDR_EXPECTED\n";
        exit(99);
      }
      char ch = addressType.getValue()[0];
      if(! (ch == 'I' || ch == 'A' || ch == 'E' || ch == 'R') ){
        cout << "Parse Error line "<< addressType.getLineNumber() << " offset "<<addressType.getColumnNumber()<< ": ADDR_EXPECTED\n";
        exit(99);
      }
      return Token<char>(addressType.getLineNumber(), addressType.getColumnNumber(), ch, addressType.getLength());
    };

  public:
    ProgramTextReader(fstream& fin, long fs) : AbstractReader(fin, fs){
      this->availableMemory = TOTAL_ADDRESSABLE_MEMORY;
    };

    int doFirstPass(){
      Token<int> prCount = getNextTokenAsInteger(true);
      this->availableMemory -= prCount.getValue();
      if(this->availableMemory < 0){
        cout << "Parse Error line "<<prCount.getLineNumber() << " offset "<<prCount.getColumnNumber()<< ": TO_MANY_INSTR\n";
        exit(99);
      }
      int iterator = 0;
      for(int iterator = 0; iterator < prCount.getValue(); iterator++){
        Token<char> addr = getAddressType();
        Token<int> instruction = getNextTokenAsInteger(false);
      } 
      return prCount.getValue();
    };

    int doSecondPass(map<int,UseList>* useList, int memoryAddress){
      Token<int> prCount = getNextTokenAsInteger(true);
      int iterator =0;
      SymbolTable& st = SymbolTable::getInstance();
      for(int iterator = 0; iterator < prCount.getValue(); iterator++){
        string warning = "";
        bool instructionOverflow = false;

        Token<char> addr = getAddressType();
        char addressing = addr.getValue();
        Token<int> instruction = getNextTokenAsInteger(false);

        int instructionVal = instruction.getValue();
        if(instructionVal > 9999){
          instructionVal = 9999;
          instructionOverflow = true;
        }

        int opcode = instructionVal / 1000;
        int operand  = instructionVal %1000;

        if(addressing == 'E'){
          map<int, UseList>::iterator mi = useList->find(operand);
          if(mi == useList->end()){
            warning = "Error: External address exceeds length of uselist; treated as immediate"; // rule 6
            addressing = 'I';
          }else{
            mi->second.setUsed(true);
            string token = mi->second.getSymbol().getToken();
            if(st.isDefined(token)){
              operand = st.getAddress(token);
            }else{
              warning = "Error: " + token + " is not defined; zero used"; // rule 4
            }
          }
        }else if(addr.getValue() == 'A' && operand >= TOTAL_ADDRESSABLE_MEMORY){
          operand = 000;
          warning = "Error: Absolute address exceeds machine size; zero used";
        }
        cout << setfill('0') << setw(3) << memoryAddress << ": ";
        cout << opcode << std::setfill('0') << std::setw(3) <<  operand << " " << warning <<"\n";
        memoryAddress++;
      }

      return 0;
    }
};

#endif
