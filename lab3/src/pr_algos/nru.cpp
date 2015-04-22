
class NRU:public AbstractPR{
  private:
    unsigned int instructionCount;
    ifstream* fin;
    unsigned int size, ofs;
    int* arr;

    int getRandomNumber(){
      ofs = ofs % size;
      int retVal = *(arr + ofs);
      ofs++;
      return retVal;
    }
  public:
    NRU(vector<pte>* pt, vector<unsigned int>* ft, vector<unsigned int>* ftop, ifstream& randFile): AbstractPR(pt, ft, ftop){
      instructionCount = 0;
      fin = &(randFile);

      *(fin) >> size;
      arr = new int[size];

      for(int i = 0; i < size; i++){
        *(fin) >> *(arr+ i); 
      }

      ofs = 0;
    }

    void update_counter(unsigned int frame_number){
    }

    int get_frame_to_replace(){
      int physical_frame = -1, m, r;

      vector<pte>* categories = new vector<pte>[4];
      for(int i = 0; i < page_table->size(); i++){
        if(page_table->at(i).present == 0){
          continue;
        }

        m = page_table->at(i).modified;
        r = page_table->at(i).referenced;

        if(m == 0 && r == 0){
          categories[0].push_back(page_table->at(i));
        }else if(m == 1 && r == 0) {
          categories[1].push_back(page_table->at(i));
        }else if(m == 0 && r == 1) {
          categories[2].push_back(page_table->at(i));
        }else if(m == 1 && r == 1){
          categories[3].push_back(page_table->at(i));
        }
      }

      for(int i = 0; i < 4; i++){
        if(categories[i].size() > 0){
          physical_frame = categories[i][getRandomNumber() % categories[i].size()].frame_number;
          break;
        }
      }
      instructionCount++;
      if(instructionCount % 10 == 0){
        for(unsigned int i = 0; i < page_table->size(); i++) {
          if(page_table->at(i).present == 1){
            page_table->at(i).referenced = 0;
          }
        }
      }

      return physical_frame;
    }
};
