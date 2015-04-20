#include "ds/pte.h"
#include "pr_algos/abstract_pr.cpp"

using namespace std;

class MMU{
  private:
    vector<pte>* page_table;
    vector<unsigned int>* frame_table;
    list<unsigned int>* free_list;
    AbstractPR* pre_algo;

  public:
    MMU(vector<pte>* pt, vector<unsigned int>* ft, list<unsigned int>* fl, AbstractPR* algo){
      page_table = pt;
      frame_table = ft;
      free_list = fl;
      pre_algo = algo;
    }

    void executeInstruction(int operation, int memRef){
    }
};
