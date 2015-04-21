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
    static const char READ = '0';
    static const char WRITE = '1';
    bool printDetailed = false;

  public:
    MMU(vector<pte>* pt, vector<unsigned int>* ft, list<unsigned int>* fl, AbstractPR* algo, char* optarg){
      page_table = pt;
      frame_table = ft;
      free_list = fl;
      pre_algo = algo;

      int i = 0;
      while(*(optarg+i) != '\0'){
        char ch = *(optarg+i);
        switch(ch){
          case 'O':
            printDetailed = true;
            break;
          case 'P':
            break;
          case 'F':
            break;
          case 'S':
            break;
        }
      }

    }

    void executeOperation(char operation, int pageNum){
      unsigned int physical_frame = -1;
      unsigned int page_table_to_unmap = -1;

      if(printDetailed){
        cout << "==> inst: " << operation << " " << pageNum << endl;
      }


      if(page_table->at(pageNum).present == 1){
        page_table->at(pageNum).referenced = 1;
        if(operation == WRITE){
          page_table->at(pageNum).modified = 1;
        }
      }
      if(free_list->size() > 0){
        physical_frame = free_list->front();
        //reduce freelist size
        //Zero the frame
        pte p = page_table->at(pageNum);
        p.present = 1;
        p.modified = 0;
        p.referenced = 1;
        p.paged_out = 0;
        p.frame_number = physical_frame;

        frame_table->at(physical_frame) = pageNum; // Reverse mapping to page table
        if(printDetailed) {
          cout << instructionCount << ": ZERO" << " " << pageNum << endl;
          cout << instructionCount << ": MAP"  << " " << pageNum << " " << physical_frame << endl;
        }
      }

      physical_frame = pre_algo->get_frame_to_replace();
      page_table_to_unmap = frame_table->at(physical_frame);
      
      pte p_to_replace = page_table->at(page_table_to_unmap);

      //unmap
      //map
    }
};
