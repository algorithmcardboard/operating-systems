#include <iostream>
#include <fstream>

using namespace std;

int main(){
	char ch;
  fstream fin("file", fstream::in);
  while(fin >> noskipws >> ch){
    cout << ch;
  }
}
