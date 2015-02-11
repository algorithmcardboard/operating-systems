#ifndef ABSTRACT_READER_H
#define ABSTRACT_READER_H

#include "../ds/token.h"

using namespace std;

class AbstractReader {

  public:
    static int lineNumber;
    static int columnNumber;

  protected:

    fstream* fin;

    AbstractReader(fstream& fin){
      this->fin = &(fin);
    }

    Token<char*> getNextToken(){
      char ch;
      int position = 0, tokenStartLine = 0, tokenStartColumn = 0;
      char* token = new char[512];
      bool tokenStart = false, isWhiteSpace = false;

      while(*(this->fin) >> ch){
        isWhiteSpace = (ch == ' ' || ch == '\n' || ch == '\t');

        AbstractReader::columnNumber++;

        if(ch == '\n'){
          AbstractReader::lineNumber++;
          AbstractReader::columnNumber = 0;
        }

        if(tokenStart && isWhiteSpace){
          token[position] = '\0';
          break;
        }else if(isWhiteSpace){
          continue;
        }else if(!tokenStart){ // token is beginning here
          tokenStartLine = AbstractReader::lineNumber;
          tokenStartColumn = AbstractReader::columnNumber;
        }

        tokenStart = true;
        token[position++] = ch;
      }
      Token<char*> newToken(tokenStartLine, tokenStartColumn, token);
      return newToken;
    }


    bool isInteger(char* string){
    }

    bool isAlphaNumeric(char* string){
    }

    virtual void doFirstPass() = 0;
    virtual void doSecondPass() = 0;
};
int AbstractReader::lineNumber = 1;
int AbstractReader::columnNumber = 0;
#endif
