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

int Process::getLastTransitionTime(){
  return lastTransitionTime;
}

void Process::setLastTransitionTime(int time){
  lastTransitionTime = time;
}
