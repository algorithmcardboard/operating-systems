using namespace std;

class Event{
  private:
    int timestamp;
    int pid;
    int oldState;
    int newState;
  public:
    Event(int, int, int, int);
};
