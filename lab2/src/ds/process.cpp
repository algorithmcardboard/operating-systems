#include "process.h"

unsigned int Process::globalPID = 0;

Process::Process(int arrivalTime, int totalCPUTime, int cpuBurst, int ioBurst, int priority){
  this->pid = globalPID++;
  this->arrivalTime = arrivalTime;
  this->totalCPUTime = totalCPUTime;
  this->cpuBurst = cpuBurst;
  this->ioBurst = ioBurst;
  this->static_priority = priority;
  this->dynamic_priority= priority - 1;
  this->currentState = CREATED;
  this->lastTransitionTime = arrivalTime;
  this->remainingTime = totalCPUTime;
  this->ioTime = 0;
  this->cpuWaitTime = 0;
  this->remainingCPUBurst = 0;
}

int Process::getPID(){
  return pid;
}

ProcessState Process::getCurrentState(){
  return currentState;
}

bool Process::hasRemainingCPU(){
  return false;
}

int Process::getCpuBurst(){
  return cpuBurst;
}

int Process::getIOBurst(){
  return ioBurst;
}

void Process::reduceRemainingTime(int burst){
  this->remainingTime -= burst;
}

int Process::getRemainingTime(){
  return remainingTime;
}

int Process::getRemainingCpuBurst(){
  return remainingCPUBurst;
}

void Process::setRemainingCpuBurst(int rcb){
  remainingCPUBurst = rcb;
}

void Process::reduceDynamicPriority(){
  this->dynamic_priority--;
}

void Process::resetDynamicPriority(){
  this->dynamic_priority = static_priority - 1;
}

int Process::getDynamicPriority(){
  return dynamic_priority;
}

int Process::getStaticPriority(){
  return static_priority;
}

int Process::getLastTransitionTime(){
  return lastTransitionTime;
}

void Process::setLastTransitionTime(int time){
  lastTransitionTime = time;
}

void Process::addIOBurst(int iob){
  ioTime += iob;
}

int Process::getIOTime(){
  return ioTime;
}

int Process::getArrivalTime(){
  return arrivalTime;
}

int Process::getTotalCPUTime(){
  return totalCPUTime;
}

void Process::addCPUWaitTime(int time){
  cpuWaitTime += time;
}

int Process::getCpuWaitingTime(){
  return cpuWaitTime;
}

int Process::getTurnaroundTime(){
  return lastTransitionTime - arrivalTime;
}

void Process::setLastScheduledId(int scheduledID){
  lastScheduledID = scheduledID;
}

int Process::getLastScheduledId(){
  return lastScheduledID;
}
