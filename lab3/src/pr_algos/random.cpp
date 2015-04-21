#include <fstream>

using namespace std;

class Random:public AbstractPR{
  private:
    ifstream* fin;
    unsigned int size, ofs;
    int* arr;
  public:
    Random(vector<pte>* pt, vector<unsigned int>* ft, vector<unsigned int>* ftop, ifstream& randFile): AbstractPR(pt, ft, ftop){
      fin = &(randFile);

      *(fin) >> size;
      arr = new int[size];

      for(int i = 0; i < size; i++){
        *(fin) >> *(arr+ i); 
      }

      ofs = 0;
    }

    int get_frame_to_replace(){
      ofs = ofs % size;
      int retVal = *(arr + ofs) % frame_table->size();
      ofs++;
      return retVal;
    }
};

