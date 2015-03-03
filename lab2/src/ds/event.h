#include<iostream>

using namespace std;

class Event{
  private:
    static unsigned int sequence;
    int timestamp;
    int seqNum;
    int pid;
    int oldState;
    int newState;
  public:
    Event(int, int, int, int);
    int getTimestamp() const;
    int getSequenceNumber() const;
    friend ostream& operator<< (ostream &out, Event &eve);
};
