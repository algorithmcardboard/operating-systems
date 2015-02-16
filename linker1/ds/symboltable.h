#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "symbol.h"
#include <vector>
#include <string>
#include <map>

using namespace std;

class SymbolTable {

  public:
    static SymbolTable& getInstance(){
      static SymbolTable instance; // Guaranteed to be destroyed.  Instantiated on first use
      return instance;
    }

    void push(Symbol s){
      map<string,int>::iterator mi = this->usedSymbols->find(s.getToken());
      if(mi != this->usedSymbols->end()){
        this->table->at(mi->second-1).setMultipleDefinitions(true);
      }else{
        this->table->push_back(s);
        this->usedSymbols->insert(pair<string, int>(s.getToken(), this->table->size()));
      }
    }

    void printSymbols(){
      this->printWarnings();
      cout << "Symbol Table\n";
      for(vector<Symbol>::iterator ci = this->table->begin(); ci != this->table->end(); ++ci){
        cout << ci->getToken() << "=" << ci->getAddress() << " ";
        if(ci->hasMultipleDefinitions()){
          cout << "Error: This variable is multiple times defined; first value used";
        }
        cout << "\n";
      }
    };

    void checkDefinitionLengths(int currentDLSize, int moduleLength, int moduleCount){
      int totalSize = this->table->size();
      for(int i = (totalSize - currentDLSize); i < totalSize; i++){
        if(this->table->at(i).getRelativeAddress() >= moduleLength){
          cout<< "Warning: Module "<< moduleCount <<": " << this->table->at(i).getToken() << " to big "<< this->table->at(i).getRelativeAddress() <<" (max="<< moduleLength-1 << ") assume zero relative\n";
          this->table->at(i).setRelativeAddress(0);
        }
      }
    }

  private:
    vector<Symbol>* table;
    map<string,int>* usedSymbols;

    SymbolTable(){ 
      this->table = new vector<Symbol>();
      this->usedSymbols = new map<string, int>();
    }

    void printWarnings(){
    }

    SymbolTable(SymbolTable const&);
    void operator=(SymbolTable const&);
};

#endif
