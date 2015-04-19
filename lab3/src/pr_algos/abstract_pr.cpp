#ifndef ABSTRACT_PR
#define ABSTRACT_PR

using namespace std;

class AbstractPR{
  protected:
    int page_table_size;
    int frame_table_size;
  public:
    AbstractPR(int pts, int fts){
      this->page_table_size = pts;
      this->frame_table_size = fts;
    }
    virtual int get_frame_to_replace() = 0;
};

#endif
