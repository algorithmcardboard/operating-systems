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
    long fileSize;

    AbstractReader(fstream& fin, long fileSize){
      this->fin = &(fin);
      this->fileSize = fileSize;
    }

    Token<char*> getNextToken(){
      char ch;
      int length = 0;
      int position = 0, tokenStartLine = AbstractReader::lineNumber, tokenStartColumn = AbstractReader::columnNumber;
      char* token = new char[512];
      bool tokenStart = false, isWhiteSpace = false, emptyLine = true;

      while(*(this->fin) >> ch){
        if(ch == '\n'){
          if(this->fin->tellg() != this->fileSize){
            AbstractReader::lineNumber++;
            AbstractReader::columnNumber = 1;
          }
          emptyLine = true;
        }else{
          emptyLine = false;
          AbstractReader::columnNumber++;
        }

        isWhiteSpace = (ch == ' ' || ch == '\n' || ch == '\t');

        if(tokenStart && isWhiteSpace){
          token[position] = '\0';
          break;
        }else if(isWhiteSpace){
          tokenStartLine = AbstractReader::lineNumber;
          tokenStartColumn = AbstractReader::columnNumber;
          continue;
        }else if(!tokenStart){ // token is beginning here
          tokenStartLine = AbstractReader::lineNumber;
          tokenStartColumn = AbstractReader::columnNumber -1;
          tokenStart = true;
          length = 0;
        }

        length++;
        token[position++] = ch;
      }
      Token<char*> newToken(tokenStartLine, tokenStartColumn, token, length);
      return newToken;
    }

    Token<int> getNextTokenAsInteger(){
      Token<char*> nextToken = getNextToken();

      char *last = 0;
      int intVal = (int) strtol(nextToken.getValue(), &last, 10);
      if(*last != 0 || intVal < 0){
        cout << "Parse Error line "<< nextToken.getLineNumber() << " offset "<< nextToken.getColumnNumber() << ": NUM_EXPECTED\n";
        exit(99);
      }
      return Token<int>(nextToken.getLineNumber(), nextToken.getColumnNumber(), intVal, nextToken.getLength());
    }

    Token<char*> getSymbol(){
      Token<char*> symbol = getNextToken();

      if(symbol.getLength() == 0){
        cout << "Parse Error line "<< symbol.getLineNumber() << " offset " << symbol.getColumnNumber()<< ": SYM_EXPECTED\n";
        exit(99);
      }

      if(symbol.getLength() > 16){
        cout << "Parse Error line "<< symbol.getLineNumber() << " offset " << symbol.getColumnNumber()<< ": SYM_TOLONG\n";
        exit(99);
      }
      char ch = symbol.getValue()[0];

      if(ch >= '0' &&  ch <= '9'){
        cout << "Parse Error line "<< symbol.getLineNumber() << " offset " << symbol.getColumnNumber()<< ": SYM_EXPECTED\n";
        exit(99);
      }

      return symbol;
    }

    virtual void doFirstPass() = 0;
    virtual void doSecondPass() = 0;
};

int AbstractReader::lineNumber = 1;
int AbstractReader::columnNumber = 1;
#endif
