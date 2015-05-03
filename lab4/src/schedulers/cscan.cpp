#include "abstract_scheduler.cpp"
#include <vector>
#include <limits.h>

using namespace std;

class CSCAN: public AbstractScheduler{
  private:
    vector<IoRequest*> request_list;
    unsigned int global_index;

  public:
    CSCAN(){
      global_index = 0;
    }

    IoRequest* get_next_track(unsigned int track_location){
      if(request_list.size() == 0){
        return NULL;
      }

      int locToErase = 0;
      IoRequest* ioToReturn = NULL;
      for(int i=0; i < request_list.size(); i++){
        if(request_list[i]->getTrackNumber() < track_location){
          continue;
        }
        locToErase = i;
        break;
      }

      ioToReturn = request_list.at(locToErase);
      request_list.erase(request_list.begin() + locToErase);
      return ioToReturn;
    }

    void add_track_request(IoRequest* req){
      int loc = request_list.size();
      for(int i = 0; i < request_list.size(); i++){
        if(req->getTrackNumber() < request_list[i]->getTrackNumber()){
          loc = i;
          break;
        }
      }
      request_list.insert(request_list.begin() + loc, req);
    }
};
