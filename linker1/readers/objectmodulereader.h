#include <iostream>
#include <fstream>
#include "definitionlistreader.h"
#include "uselistreader.h"
#include "programtextreader.h"

using namespace std;

class ObjectModuleReader{
  static const char* NAME;

  public:
    void printName(){
      cout << NAME;
    }
};
