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

    int doSecondPass(map<int,UseList>* useList, map<int, int>* moduleLengths, int moduleCount, int moduleBaseAddress){
      int memoryAddress = 0;
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

        if(addressing == 'I' && instructionOverflow){
          warning = "Error: Illegal immediate value; treated as 9999"; // rule 10
        }else if(instructionOverflow){
          warning = "Error: Illegal opcode; treated as 9999"; //rule 11
        } else if(addressing == 'R'){
          if(operand >= moduleLengths->at(moduleCount)){
            operand = moduleBaseAddress;
            warning = "Error: Relative address exceeds module size; zero used"; // rule 9
          }else{
            operand = operand+moduleBaseAddress;
          }
        }else if(addressing == 'E'){
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
              warning = "Error: " + token + " is not defined; zero used"; // rule 3
              operand = 0;
            }
          }
        }else if(addressing == 'A' && operand >= TOTAL_ADDRESSABLE_MEMORY){
          operand = 000;
          warning = "Error: Absolute address exceeds machine size; zero used"; // rule 8
        }

        cout << setfill('0') << setw(3) << (moduleBaseAddress + memoryAddress) << ": ";
        cout << opcode << std::setfill('0') << std::setw(3) <<  operand << " " << warning <<"\n";

        memoryAddress++;
      }

      for(map<int, UseList>::iterator it = useList->begin(); it != useList->end(); ++it){
        if(!it->second.getUsage()){
          cout << "Warning: Module "<<moduleCount<<": "<<it->second.getToken()<<" appeared in the uselist but was not actually used\n";
        }
      }

      return memoryAddress;
    }
};

#endif
