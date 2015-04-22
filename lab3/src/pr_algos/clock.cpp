class Clock:public AbstractPR{
  private:
    unsigned int hand;
  public:
    Clock(vector<pte>* pt, vector<unsigned int>* ft, vector<unsigned int>* ftop): AbstractPR(pt, ft, ftop){
      hand = 0;
    }

    void update_counter(unsigned int frame_number){
    }

    int get_frame_to_replace(){
      int physical_frame = frame_table->at(hand);
      int pt_index = ftop->at(physical_frame);

      while(page_table->at(pt_index).referenced != 0){
        page_table->at(pt_index).referenced = 0;

        hand = (hand+1) % frame_table->size();

        physical_frame = frame_table->at(hand);
        pt_index = ftop->at(physical_frame);
      }
      hand = (hand+1)%frame_table->size();
      return physical_frame;
    }
};
