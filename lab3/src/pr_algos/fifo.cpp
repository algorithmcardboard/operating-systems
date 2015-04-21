class FIFO :public AbstractPR{
  private:
    unsigned int fifo_index;
  public:
    FIFO(vector<pte>* pt, vector<unsigned int>* ft, vector<unsigned int>* ftop): AbstractPR(pt, ft, ftop){
    }

    int get_frame_to_replace(){
      int physical_frame = frame_table->front();
      frame_table->erase(frame_table->begin());
      frame_table->push_back(physical_frame);

      return physical_frame;
    }
};
