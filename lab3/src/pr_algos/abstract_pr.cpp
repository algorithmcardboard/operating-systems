#ifndef ABSTRACT_PR
#define ABSTRACT_PR

#include <vector>
#include "../ds/pte.h"

using namespace std;

class AbstractPR{
  protected:
    vector<pte>* page_table;
    vector<unsigned int>* frame_table;

  public:
    AbstractPR(vector<pte>* pt, vector<unsigned int>* ft){
      this->page_table = pt;
      this->frame_table = ft;
    }

    virtual int get_frame_to_replace() = 0;
};

#endif
