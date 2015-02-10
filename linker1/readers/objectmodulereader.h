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
      this->fin = new fstream(this->fileName, fstream::in);

      this->dflReader = new DefinitionListReader(*(this->fin));
      this->uslReader = new UseListReader(*(this->fin));
      this->prtReader = new ProgramTextReader(*(this->fin));
    }

    /* RAIM */
    ~ObjectModuleReader(){
      if(this->fin){
        this->fin->close();
      }
    }

    list<ObjectModule> doFirstPass(){

      list<ObjectModule> objModules;
      char ch;

      while(!this->fin->eof()){
        this->dflReader->doFirstPass();
        this->uslReader->doFirstPass();
        this->prtReader->doFirstPass();
      }
      cout << " eof check is "<< this->fin->eof();

      return objModules;
    }
};

#endif
