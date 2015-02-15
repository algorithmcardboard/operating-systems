#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include "token.h"

using namespace std;

class Symbol{
  private:
    int lineNumber;
    int columnNumber;
    bool multipleDefinitions;
    bool isUsed;
    string token;
    int moduleBaseAddress;
    int relativeAddress;

  public:
    Symbol(Token<char*> t){
      this->lineNumber = t.getLineNumber();
      this->columnNumber = t.getColumnNumber();
      this->token = t.getValue();

      this->isUsed = false;
      this->multipleDefinitions = false;
      this->moduleBaseAddress = 0;
    }

    void setRelativeAddress(int relativeAddress){
      this->relativeAddress = relativeAddress;
    };

    int getRelativeAddress(){
      return this->relativeAddress;
    }

    void setModuleBaseAddress(int moduleBaseAddress){
      this->moduleBaseAddress = moduleBaseAddress;
    };

    string getToken(){
      return this->token;
    }

    int getAddress(){
      return this->moduleBaseAddress  + this->relativeAddress;
    }

    void setMultipleDefinitions(bool multipleDefinitions){
      this->multipleDefinitions = multipleDefinitions;
    }

    bool hasMultipleDefinitions(){
      return multipleDefinitions;
    }
};

#endif
