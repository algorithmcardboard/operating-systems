#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv){
  bool verbose = false, fscan = false, request_details = false;
  while((c = getopt(argc, argv, "s:vfd:")) != -1){
    switch(c){
      case 's':
        break;
      case 'v':
        verbose = true;
        break;
      case 'f':
        fscan = true;
        break;
      case 'd':
        request_details = true;
        break;
    }
  }
}
