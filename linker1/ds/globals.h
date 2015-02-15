#ifndef GLOBALS_H
#define GLOBALS_H

using namespace std;

class Globals{

  private:
    currentBaseAddress = 0;

  public:

    int getModuleBaseAddress(){
      return currentBaseAddress;
    }

    Globals& getInstance(){
      static Globals g;
      return g;
    }

    Globals(){}
    Globals(Globals const&);
    void operator=(Globals const&);
};

#endif
