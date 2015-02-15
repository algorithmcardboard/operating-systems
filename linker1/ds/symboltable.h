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

  private:
    vector<Symbol>* table;
    map<string,int>* usedSymbols;

    SymbolTable(){ 
      this->table = new vector<Symbol>();
      this->usedSymbols = new map<string, int>();
    }

    void printWarnings(){
    }

    // C++ 03
    // ========
    // Dont forget to declare these two. You want to make sure they
    // are unacceptable otherwise you may accidentally get copies of
    // your singleton appearing.
    SymbolTable(SymbolTable const&);
    void operator=(SymbolTable const&);

    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.
    //SymbolTable(SymbolTable const&) = delete;
    //void operator=(SymbolTable const&) = delete;
};

#endif
