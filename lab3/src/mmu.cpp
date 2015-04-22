#include "ds/pte.h"
#include "pr_algos/abstract_pr.cpp"
#include <iomanip>

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

    bool printDetailed, pageTableRequired, frameTableRequired, summaryRequired;

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
      pageTableRequired = false;
      frameTableRequired = false;
      summaryRequired = false;

      int i = 0;
      while(*(optarg+i) != '\0'){
        char ch = *(optarg+i);
        switch(ch){
          case 'O':
            printDetailed = true;
            break;
          case 'P':
            pageTableRequired = true;
            break;
          case 'F':
            frameTableRequired = true;
            break;
          case 'S':
            summaryRequired = true;
            break;
        }
        i++;
      }
    }

    void executeOperation(char operation, int pageNum){
      unsigned int physical_frame = -1;
      unsigned int old_page_table_to_unmap = -1;

      if(instruction_count %10 == 0){
      }

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
          cout << instruction_count << ": ZERO " << setfill(' ') << setw(8) << physical_frame << endl;
          cout << instruction_count << ": MAP  " << setfill(' ') << setw(4) << pageNum << setw(4) << physical_frame << endl;
        }
        zero_counter++;
        map_counter++;
      }else{
        physical_frame = pre_algo->get_frame_to_replace();

        old_page_table_to_unmap = ftop->at(physical_frame);
        
        page_table->at(old_page_table_to_unmap).present = 0;
        page_table->at(old_page_table_to_unmap).referenced = 0;
        //cout << "resetting reference um "<< old_page_table_to_unmap << endl;

        if(printDetailed){
          cout << instruction_count << ": UNMAP"  << setfill(' ') << setw(4) << old_page_table_to_unmap << setw(4) << physical_frame << endl;
        }

        unmap_counter++;

        if(page_table->at(old_page_table_to_unmap).modified == 1){
          page_table->at(old_page_table_to_unmap).paged_out = 1;
          page_table->at(old_page_table_to_unmap).modified = 0;

          if(printDetailed){
            cout << instruction_count << ": OUT  " << setfill(' ') << setw(4) << old_page_table_to_unmap << setw(4) << physical_frame << endl;
          }

          out_counter++;
        }

        page_table->at(pageNum).frame_number = physical_frame;
        ftop->at(physical_frame) = pageNum;  //reverse mapping

        if(page_table->at(pageNum).paged_out == 1){
          if(printDetailed){
            cout << instruction_count << ": IN   " << setfill(' ') << setw(4) << pageNum << setw(4) << physical_frame << endl;
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
      //cout << "Setting referenced in "<< pageNum << endl;
      page_table->at(pageNum).present = 1;
      if(operation == WRITE){
        page_table->at(pageNum).modified = 1;
      }
      instruction_count++;
    }

    void printSummary(){
      if(!summaryRequired){
        return;
      }

      unsigned long long cost;

      cost =  instruction_count + 400 * (map_counter + unmap_counter)
      + 3000 * (in_counter + out_counter)
      + 150 * zero_counter;


      cout << "SUM " << instruction_count << " U=" << unmap_counter << " M=" << map_counter;
      cout << " I=" << in_counter << " O=" << out_counter << " Z=" << zero_counter << " ===> " << cost << endl;

    }

    void printPageTable(){
      if(!pageTableRequired){
        return;
      }

      for (int i = 0; i < page_table->size(); i++) {
        if (page_table->at(i).present == 1) {
          cout << i << ":";
          page_table->at(i).referenced == 1? cout << "R": cout << "-";
          page_table->at(i).modified == 1? cout << "M": cout << "-";
          page_table->at(i).paged_out == 1? cout << "S": cout << "-";
          cout << " ";
        } else {
          page_table->at(i).paged_out == 1? cout << "# ": cout << "* ";
        }
      }
      cout << endl;
    }

    void printFrameTable(){
      if(!frameTableRequired){
        return;
      }

      for (int i = 0; i < ftop->size(); i++) {
          (ftop->at(i)== -1)? cout << "* " : cout << ftop->at(i) << " ";            
      }
      cout << endl;
    }
};
