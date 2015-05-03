#ifndef ABSTRACT_SCHEDULER_CPP
#define ABSTRACT_SCHEDULER_CPP

#include <list>
#include "../ds/io_request.cpp"

using namespace std;

class AbstractScheduler{
  public:
    virtual IoRequest* get_next_track() = 0;
    virtual void add_track_request(IoRequest*) = 0;
};

#endif
