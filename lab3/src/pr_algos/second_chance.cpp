class SecondChance:public AbstractPR{
  private:
  public:
    SecondChance(vector<pte>* pt, vector<unsigned int>* ft, vector<unsigned int>* ftop): AbstractPR(pt, ft, ftop){
    }

    int get_frame_to_replace(){
      int physical_frame = frame_table->front();
      frame_table->erase(frame_table->begin());
      frame_table->push_back(physical_frame);

      int pt_index = ftop->at(physical_frame);
      page_table->at(pt_index).referenced = 0;

      for(int i = 0; i < frame_table->size(); i++){
        pt_index = ftop->at(i);
        if(page_table->at(pt_index).referenced == 0){
          break;
        }
      }

      return page_table->at(pt_index).frame_number;
    }
};

