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
        //this->uslReader->doFirstPass();
        //this->prtReader->doFirstPass();
      }

      return objModules;
    }
};

#endif
