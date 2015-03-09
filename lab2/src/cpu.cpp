#include "cpu.h"

using namespace std;

// Destructor
CPU::~CPU(){
  inFile->close();
  randFile->close();
  delete inFile;
  delete randFile;
}

Scheduler* CPU::getScheduler(char* schedulerSpec){
  Scheduler* scheduler;
  int quantum;
  cout << "Scheduler is "<< schedulerSpec << endl;
  char ch = schedulerSpec[0];
  switch(ch){
    case 'F':
      scheduler = new FCFS();
      break;
    case 'L':
      scheduler = new LCFS();
      break;
    case 'S':
      scheduler = new SJF();
      break;
    case 'P':
      schedulerSpec++;
      quantum = atoi(schedulerSpec);
      cout << "Quantum is "<< quantum << endl;
      scheduler = new PriorityScheduler(quantum);
      break;
    case 'R':
      schedulerSpec++;
      quantum = atoi(schedulerSpec);
      cout << "Quantum is "<< quantum << endl;
      scheduler = new RoundRobin(quantum);
      break;
    default:
      return NULL;
  }
}

// Constructor 
CPU::CPU(char* inputFileName, char* randFileName, char* schedulerSpec){
  good = true;
  inFile = new ifstream(inputFileName);
  randFile = new ifstream(randFileName);

  if(!inFile->good()){
    good = false;
    error += "Invalid input file\n";
  }

  if(!randFile->good()){
    good = false;
    error += "Invalid rand file\n";
  }
  randGen = new RandomNumberGenerator(*(randFile));

  curScheduler = getScheduler(schedulerSpec);
}

void CPU::populateEventQueue(){
  int arrivalTime, totalCPU, cpuBurst, ioBurst;
  while(*(inFile) >> arrivalTime >> totalCPU >> cpuBurst >> ioBurst){
    int priority =  randGen->getStaticPriority();
    Process* newProcess = new Process(arrivalTime, totalCPU, cpuBurst, ioBurst, priority);
    Event* eve = new Event(arrivalTime, newProcess->getPID(), newProcess->getCurrentState(), READY);
    ProcessTable::getInstance().push(newProcess);
    eventQueue.push(eve);
  }
}

/*
 * All public methods below this
 */

bool CPU::isGood(){
  return good;
}

string CPU::getError(){
  return error;
}

void CPU::start(){
  populateEventQueue();

  //randGen->printSeed();

  unsigned int time = 0;

  while(!eventQueue.empty()){
    time = eventQueue.top()->getTimestamp();
    while(!eventQueue.empty() && eventQueue.top()->getTimestamp() == time){
      Event* eve = eventQueue.top();
      cout << "Getting events at time "<< time << " " << *(eve) << endl;

      Event::Transition eventTransition =  eve->getTransition();
      cout << "Got the transition " << endl;
      Process* p = ProcessTable::getInstance().getProcess(eve->getPID());
      switch(eventTransition){
        case Event::T_CREATE:
          //Initialize process parameters such as priority and push it to scheduler
          curScheduler->addProcess(p);
          break;
        case Event::T_RUN:
          break;
        case Event::T_BLOCK:
          break;
        case Event::T_UNBLOCK:
          break;
        case Event::T_PREEMPT:
          break;
        case Event::T_TERMINATE:
          break;
      }
      eventQueue.pop();
      delete eve;
    }
    cout << "Event queue end" << endl;
  }
}
