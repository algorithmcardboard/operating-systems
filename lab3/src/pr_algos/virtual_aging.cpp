class VirtualAging:public AbstractPR{
  private:
    vector<unsigned int>* counter;
    int numPages;

  public:
    VirtualAging(vector<pte>* pt, vector<unsigned int>* ft, vector<unsigned int>* ftop, int np): AbstractPR(pt, ft, ftop){
      numPages = np;
      counter = new vector<unsigned int>(np, 0);
    }

    void update_counter(unsigned int frame_number){
    }

    int get_frame_to_replace(){

      int physical_frame = -1;
      for(int i = 0; i < numPages; i++){
        unsigned int& cValue = counter->at(i);

        cValue = (cValue >> 1) | (page_table->at(i).referenced << 31);
        if(page_table->at(i).present == 1){
          page_table->at(i).referenced = 0;
        }
        counter->at(i) = cValue;
      }

      unsigned int min = 0xffffffff, tmp, min_index, fNumber = 0;
      for(int i = 0; i < page_table->size(); i++){
        if(page_table->at(i).present != 1){
          continue;
        }
        physical_frame = page_table->at(i).frame_number;
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
