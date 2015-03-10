#ifndef PROCESS_STATE_H
#define PROCESS_STATE_H

enum ProcessState{
  CREATED=1,
  READY=2,
  RUNNING=3,
  BLOCKED=4,
  TERMINATED=5
};

#endif
