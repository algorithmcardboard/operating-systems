#ifndef OBJECT_MODULE_READER_H
#define OBJECT_MODULE_READER_H

#include <iostream>
#include <fstream>
#include <list>

#include "definitionlistreader.h"
#include "uselistreader.h"
#include "programtextreader.h"

#include "../ds/objectmodule.h"

using namespace std;

class ObjectModuleReader{

  private:
    char* fileName;
    fstream* fin;
    DefinitionListReader* dflReader;
    UseListReader* uslReader;
    ProgramTextReader* prtReader;

  public:
    ObjectModuleReader(char* file_name){
      this->fileName = file_name;

      this->fin = new fstream(this->fileName, fstream::in | ios::ate); //open at EOF to get the file size

      long size = this->fin->tellg();

      this->fin->seekg(0);

      this->fin->unsetf(ios_base::skipws);

      this->dflReader = new DefinitionListReader(*(this->fin), size);
      this->uslReader = new UseListReader(*(this->fin), size);
      this->prtReader = new ProgramTextReader(*(this->fin), size);
    }

    /* RAII - Resource Allocation Is Initialization */
    ~ObjectModuleReader(){
      if(this->fin){
        this->fin->close();
      }
    }

    list<ObjectModule> doFirstPass(){
      int length = 0;

      list<ObjectModule> objModules;
      char ch;

      while(!this->fin->eof()){
        int numDefinitions = this->dflReader->doFirstPass(length);
        this->uslReader->doFirstPass();
        int moduleLength = this->prtReader->doFirstPass();
        length += moduleLength;
        SymbolTable& instance = SymbolTable::getInstance();
        instance.checkDefinitionLengths(numDefinitions, moduleLength);
        //check size in symboltable and warn if address in DL greater than module size.
      }
      SymbolTable& instance = SymbolTable::getInstance();
      instance.printSymbols();

      return objModules;
    }
};

#endif
