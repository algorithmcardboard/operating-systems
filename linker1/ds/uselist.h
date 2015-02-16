#ifndef USELIST_H
#define USELIST_H

#include <string>
#include "symbol.h"

using namespace std;

class UseList{
  private:
    Symbol* s;
    bool isUsed;

  public:
    UseList(Symbol* s){
      this->s = s;
    }

    string getToken(){
      return this->s->getToken();
    };

    void setUsed(bool isUsed){
      this->isUsed = isUsed;
    };

    bool getUsage(){
      return this->isUsed;
    }

    Symbol getSymbol(){
      return *(this->s);
    }
};

#endif
