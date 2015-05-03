#include "abstract_scheduler.cpp"
#include <vector>
#include <limits.h>

using namespace std;

class SCAN: public AbstractScheduler{
  private:
    vector<IoRequest*> request_list;
    bool positive;

  public:
    SCAN(){
      positive = true;
    }

    IoRequest* get_next_track(unsigned int track_location){
      if(request_list.size() == 0){
        return NULL;
      }
      IoRequest *minToLeft = NULL, *minToRight = NULL, *ioToReturn = NULL;
      int locToErase = -1;
      int minLeftDistance = INT_MAX, minRightDistance = INT_MAX, leftLoc = -1, rightLoc = -1;
      unsigned int track_distance;
      bool skip = false;
      for(int i=0; i < request_list.size(); i++){
        track_distance = abs(request_list[i]->getTrackNumber() - track_location);
        if(track_distance == 0){
          skip = true;
          locToErase = i;
          ioToReturn = request_list[i];
          break;
        }
        //cout << request_list[i]->getTrackNumber() << ":" << track_distance << " ";
        if(request_list[i]->getTrackNumber() < track_location){
          if(track_distance < minLeftDistance){
            minToLeft = request_list[i];
            leftLoc = i;
            minLeftDistance = track_distance;
          }
        }else{
          if(track_distance < minRightDistance){
            minToRight = request_list[i];
            rightLoc = i;
            minRightDistance = track_distance;
          }
        }
      }
      //cout << endl;

      if(!skip){
        if(positive && minToRight == NULL){
          ioToReturn = minToLeft;
          locToErase = leftLoc;

          positive = !positive;
        }else if(positive && minToRight != NULL){
          ioToReturn = minToRight;
          locToErase = rightLoc;
        }else if(!positive && minToLeft == NULL){
          ioToReturn = minToRight;
          locToErase = rightLoc;

          positive = !positive;
        }else{
          ioToReturn = minToLeft;
          locToErase = leftLoc;
        }
      }

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


