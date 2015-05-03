#include "abstract_scheduler.cpp"
#include <vector>
#include <limits.h>

using namespace std;

class SSTF: public AbstractScheduler{
  private:
    vector<IoRequest*> request_list;

  public:
    IoRequest* get_next_track(unsigned int track_location){
      if(request_list.size() == 0){
        return NULL;
      }
      int loc = 0, track_distance, minimum_distance = INT_MAX;
      for(int i = 0; i < request_list.size(); i++){
        track_distance = abs(request_list[i]->getTrackNumber() - track_location);
        if(track_distance < minimum_distance){
          loc = i;
          minimum_distance = track_distance;
        }
      }

      IoRequest* req = request_list.at(loc);
      request_list.erase(request_list.begin() + loc);
      return req;
    }

    void add_track_request(IoRequest* req){
      request_list.push_back(req);
    }
};

