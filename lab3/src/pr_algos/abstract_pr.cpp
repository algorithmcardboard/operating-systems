#ifndef ABSTRACT_PR
#define ABSTRACT_PR

#include <vector>
#include "../ds/pte.h"

using namespace std;

class AbstractPR{
  protected:
    vector<pte>* page_table;
    vector<unsigned int>* frame_table;
    vector<unsigned int>* ftop;

  public:
    AbstractPR(vector<pte>* pt, vector<unsigned int>* ft, vector<unsigned int>* fp){
      this->page_table = pt;
      this->frame_table = ft;
      this->ftop = fp;
    }

    virtual void update_counter(unsigned int frame_number) = 0;

    virtual int get_frame_to_replace() = 0;
};

#endif
