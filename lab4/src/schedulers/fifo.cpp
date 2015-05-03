#include "abstract_scheduler.cpp"
#include <vector>

using namespace std;

class FIFO : public AbstractScheduler{
  private:
    vector<IoRequest*> request_list;

  public:
    IoRequest* get_next_track(unsigned int track_location){
      //cout << "Size of request list is " << request_list.size() << endl;
      if(request_list.size() == 0){
        return NULL;
      }
      IoRequest* req = request_list.front();
      request_list.erase(request_list.begin());
      return req;
    }

    void add_track_request(IoRequest* req){
      request_list.push_back(req);
    }
};
