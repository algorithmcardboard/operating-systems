#ifndef OBJECT_MODULE_READER_H
#define OBJECT_MODULE_READER_H

#include <iostream>
#include <fstream>
#include <list>

#include "definitionlistreader.h"
#include "uselistreader.h"
#include "programtextreader.h"

using namespace std;

class ObjectModuleReader{

  private:
    char* fileName;
    fstream* fin;
    DefinitionListReader* dflReader;
    UseListReader* uslReader;
    ProgramTextReader* prtReader;
    map<int, int>* moduleLengths;

  public:
    ObjectModuleReader(char* file_name){
      this->fileName = file_name;

      this->fin = new fstream(this->fileName, fstream::in | ios::ate); //open at EOF to get the file size
      if(!this->fin->good()){
        cout << "Not a valid input file <"<<file_name<<">\n";
        exit(99);
      }

      long size = this->fin->tellg();

      this->fin->seekg(0);

      this->fin->unsetf(ios_base::skipws);

      this->dflReader = new DefinitionListReader(*(this->fin), size);
      this->uslReader = new UseListReader(*(this->fin), size);
      this->prtReader = new ProgramTextReader(*(this->fin), size);

      this->moduleLengths = new map<int, int>();
    }

    /* RAII - Resource Allocation Is Initialization */
    ~ObjectModuleReader(){
      if(this->fin){
        this->fin->close();
      }
    }

    void doFirstPass(){
      int length = 0;
      int moduleCount = 1;

      char ch;

      while(!this->fin->eof()){
        int numDefinitions = this->dflReader->doFirstPass(length, moduleCount);
        if(this->fin->eof()){
          break;
        }
        this->uslReader->doFirstPass();
        int moduleLength = this->prtReader->doFirstPass();
        length += moduleLength;
        SymbolTable& instance = SymbolTable::getInstance();
        instance.checkDefinitionLengths(numDefinitions, moduleLength, moduleCount);
        this->moduleLengths->insert(pair<int, int>(moduleCount, moduleLength));
        moduleCount++;
        //check size in symboltable and warn if address in DL greater than module size.
      }
      SymbolTable& instance = SymbolTable::getInstance();
      instance.printSymbols();
    }

    void firstPassCleanup(){
      cout << "\n";
      this->fin->clear();
      this->fin->seekg(0);
      AbstractReader::cleanup();
      cout <<"Memory Map\n";
    }

    void doSecondPass(){
      int memoryAddress = 0;
      int moduleBaseAddress = 0;
      int moduleCount = 1;
      while(!this->fin->eof()){
        this->dflReader->doSecondPass();
        if(this->fin->eof()){
          break;
        }
        map<int,UseList>* useList = this->uslReader->doSecondPass();
        moduleBaseAddress += this->prtReader->doSecondPass(useList, this->moduleLengths, moduleCount, moduleBaseAddress);
        moduleCount++;
        /* print unused symbols from uselist */
      }
    };
};

#endif
