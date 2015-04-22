class VirtualClock:public AbstractPR{
  private:
    unsigned int hand;
  public:
    VirtualClock(vector<pte>* pt, vector<unsigned int>* ft, vector<unsigned int>* ftop): AbstractPR(pt, ft, ftop){
      hand = 0;
    }

    void update_counter(unsigned int frame_number){
    }

    int get_frame_to_replace(){
      int physical_frame = -1;

      while(true){
        physical_frame = page_table->at(hand).frame_number;
        if(page_table->at(hand).present == 1){
          if(page_table->at(hand).referenced == 0){
            break;
          }
          page_table->at(hand).referenced = 0;
        }
        hand = (hand+1)%page_table->size();
      }
      hand = (hand+1)%page_table->size();
      return physical_frame;
    }
};
