#include <limits.h>

class Aging:public AbstractPR{
  private:
    vector<unsigned int>* counter;
    int numFrames;

  public:
    Aging(vector<pte>* pt, vector<unsigned int>* ft, vector<unsigned int>* ftop, int nf): AbstractPR(pt, ft, ftop){
      numFrames = nf;
      counter = new vector<unsigned int>(nf, 0);
    }

    void update_counter(unsigned int frame_number){
    }

    int get_frame_to_replace(){

      int physical_frame = -1, pt_index = -1;
      for(int i = 0; i < numFrames; i++){
        physical_frame = frame_table->at(i);
        pt_index = ftop->at(physical_frame);

        unsigned int& cValue = counter->at(i);

        cValue = (cValue >> 1) | (page_table->at(pt_index).referenced << 31);
        page_table->at(pt_index).referenced = 0;

        counter->at(i) = cValue;
      }

      unsigned int min = 0xffffffff, tmp, min_index, fNumber = 0;
      for(int i = 0; i < frame_table->size(); i++){
        physical_frame = frame_table->at(i);
        tmp = counter->at(i);

        if(tmp <  min){
          min = tmp;
          fNumber = physical_frame;
          min_index = i;
        }
      }
      counter->at(min_index) = 0;
      return fNumber;
    }
};
