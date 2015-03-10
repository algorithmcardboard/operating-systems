#Linker - Lab1

**Author** Anirudhan Jegannathan Rajagopalan

**N-Number** N18824115

**Email** ajr619@nyu.edu

##How to compile?
    make setup
    make clean
    make

##How to run?
    Run the 'scheduler' object created at ../bin folder.  It takes -s, -v inputfile randfile as argument. Arguments can be passed in any order.

**DataStructurees**
####Process Table
A map of pid->process*  which has all the process that got created in the system.
####Event
unsigned sequenceNumber (for sorting the event priority queue), pid, timestamp, beginState, endState
####Process
Denotes a running process

##Files
**Main File**
  cpu.cpp

**./ds folder**
  Contains the various data structures used by the scheduler.

**./scheduler folder**
  Has the various schedulers
  * *AbstractSchedulers is the base class of all schedulers.  It has three virtual functions: getName, add_process & get_next_process
  * * Separate files for each type of schedulers - FCFS, LCFS, SJF, RR and Prio
