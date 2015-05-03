#include <vector>
#include "event.cpp"

using namespace std;

class EventQueue{
  private:
    vector<Event*> eventQueue;
  public:
    void push(Event* eve){
      int loc = eventQueue.size();
      for(int i = 0; i <  eventQueue.size(); i++){
        if(eve->getTimestamp() < eventQueue[i]->getTimestamp()){
          loc = i;
          break;
        }
      }
      eventQueue.insert(eventQueue.begin() + loc, eve);
    };

    Event* pop(){
      if(eventQueue.size() == 0){
        //cout << "returning null as size " << endl;
        return NULL;
      }
      //cout << "size of eventqueue is " << eventQueue.size() << endl;
      Event* e = eventQueue.front();
      eventQueue.erase(eventQueue.begin());
      return e;
    };
};
