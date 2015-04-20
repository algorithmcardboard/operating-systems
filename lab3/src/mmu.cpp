#include "ds/pte.h"
#include "pr_algos/abstract_pr.cpp"

/*
struct pte{
  unsigned int present:1;
  unsigned int modified:1;
  unsigned int referenced:1;
  unsigned int paged_out:1;
  unsigned int frameNumber:6;
};
 */
using namespace std;

class MMU{
  private:
    vector<pte>* page_table;
    vector<unsigned int>* frame_table;
    list<unsigned int>* free_list;
    AbstractPR* pre_algo;

    pte getPage(int memRef){
      if(page_table->at(memRef).present == 1){
        cout << "inside if "<< endl;
        return page_table->at(memRef);
      }
    }

  public:
    MMU(vector<pte>* pt, vector<unsigned int>* ft, list<unsigned int>* fl, AbstractPR* algo){
      page_table = pt;
      frame_table = ft;
      free_list = fl;
      pre_algo = algo;
    }

    void executeRead(int memRef){
      /*
       */
      pte entry = getPage(memRef);
    }

    void executeWrite(int memRef){
      /*
       */
      pte entry = getPage(memRef);
    }
};
