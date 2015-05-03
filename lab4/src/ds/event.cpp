#ifndef EVENT_CPP
#define EVENT_CPP

#include <iostream>

using namespace std;

class Event{
  private:
    unsigned int timestamp, track, id, op;
  public:
    Event(unsigned int time, unsigned int track_number, unsigned int io_id, unsigned int operation){
      timestamp = time;
      track = track_number;
      id = io_id;
      op = operation;
    }

    unsigned int getTimestamp(){
      return timestamp;
    }

    unsigned int getOperation(){
      return op;
    }

    unsigned int getId(){
      return id;
    }

    unsigned int getTrack(){
      return track;
    }

    friend ostream& operator<< (ostream &out, Event &eve){
      out << eve.timestamp << " " << eve.track << " " << eve.id << " " << eve.op << endl;
    }
};

#endif
