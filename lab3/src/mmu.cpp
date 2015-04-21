#include "ds/pte.h"
#include "pr_algos/abstract_pr.cpp"
#include <iomanip>

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
    static const char READ = '0';
    static const char WRITE = '1';

    vector<pte>* page_table;
    vector<unsigned int>* frame_table;
    vector<unsigned int>* ftop;
    AbstractPR* pre_algo;
    unsigned int max_frames;

    unsigned int instruction_count;
    unsigned int zero_counter;
    unsigned int map_counter;
    unsigned int unmap_counter;
    unsigned int out_counter;
    unsigned int in_counter;

    bool printDetailed;

  public:
    MMU(vector<pte>* pt, vector<unsigned int>* ft, vector<unsigned int>* fp, AbstractPR* algo, unsigned int frames, char* optarg){
      page_table = pt;
      frame_table = ft;
      ftop = fp;
      pre_algo = algo;

      max_frames = frames;

      instruction_count = 0;
      zero_counter = 0;
      map_counter = 0;
      unmap_counter = 0;
      out_counter = 0;
      in_counter = 0;

      printDetailed = false;

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
        i++;
      }
    }

    void executeOperation(char operation, int pageNum){
      unsigned int physical_frame = -1;
      unsigned int old_page_table_to_unmap = -1;

      if(printDetailed){
        cout << "==> inst: " << operation << " " << pageNum << endl;
      }

      if(page_table->at(pageNum).present == 1){
        //do nothing
      }else if(frame_table->size() < max_frames){
        physical_frame = frame_table->size();
        frame_table->push_back(physical_frame);
        //reduce freelist size
        //Zero the frame
        pte p = page_table->at(pageNum);
        p.present = 1;
        p.modified = 0;
        p.referenced = 1;
        p.paged_out = 0;
        p.frame_number = physical_frame;

        page_table->at(pageNum) = p;

        ftop->at(physical_frame) = pageNum; // Reverse mapping to page table
        if(printDetailed) {
          cout << instruction_count << ": ZERO " << setfill(' ') << setw(8) << pageNum << endl;
          cout << instruction_count << ": MAP  " << setfill(' ') << setw(4) << pageNum << setw(4) << physical_frame << endl;
        }
        zero_counter++;
        map_counter++;
      }else{
        physical_frame = pre_algo->get_frame_to_replace();

        old_page_table_to_unmap = ftop->at(physical_frame);
        
        pte old_pte_to_replace = page_table->at(old_page_table_to_unmap);
        
        old_pte_to_replace.present = 0;
        old_pte_to_replace.referenced = 0;

        if(printDetailed){
          cout << instruction_count << ": UNMAP"  << setfill(' ') << setw(4) << old_page_table_to_unmap << setw(4) << physical_frame << endl;
        }

        page_table->at(old_page_table_to_unmap) = old_pte_to_replace;

        unmap_counter++;

        if(old_pte_to_replace.modified == 1){
          old_pte_to_replace.paged_out = 1;
          old_pte_to_replace.modified = 0;

          if(printDetailed){
            cout << instruction_count << ": OUT  " << setfill(' ') << setw(4) << old_page_table_to_unmap << physical_frame << endl;
          }

          out_counter++;
        }

        ftop->at(physical_frame) = pageNum;  //reverse mapping

        if(page_table->at(pageNum).paged_out == 1){
          if(printDetailed){
            cout << instruction_count << ": IN   " << setfill(' ') << setw(4) << pageNum << physical_frame << endl;
          }
          in_counter++;
        }else{
          if(printDetailed){
            cout << instruction_count << ": ZERO " << setfill(' ') << setw(8) << physical_frame << endl;
          }
          zero_counter++;
        }
        if(printDetailed){
          cout << instruction_count << ": MAP  "  << setfill(' ') << setw(4) << pageNum << setw(4) << physical_frame << endl;
        }

        map_counter++;
      }

      page_table->at(pageNum).referenced = 1;
      page_table->at(pageNum).present = 1;
      if(operation == WRITE){
        page_table->at(pageNum).modified = 1;
      }
      instruction_count++;
    }
};
