#include <iostream>
#include <fstream>
#include "readers/objectmodulereader.h"

using namespace std;

int main(int argc, char* argv[]){
  if(argc != 2){
    cout << "Command should be called with the input file as argument.";
  }
	char ch;
  fstream fin("file", fstream::in);
}
