#ifndef TOKEN_H
#define TOKEN_H

using namespace std;

template <class T> 
class Token{
  private:
    int lineNumber;
    int columnNumber;
    T token;

  public:
    Token(int lineNumber, int columnNumber, T token){
      this->lineNumber = lineNumber;
      this->columnNumber = columnNumber;
      this->token = token;
    }

    int getLineNumber(){
      return this->lineNumber;
    }

    int getColumnNumber(){
      return this->columnNumber;
    }

    T getValue(){
      return this->token;
    }
};

#endif
