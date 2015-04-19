class FIFO :public AbstractPR{
  private:
  public:
    FIFO(vector<pte>* pt, vector<unsigned int>* ft): AbstractPR(pt, ft){
    }

    int get_frame_to_replace(){
      return 0;
    }
};
