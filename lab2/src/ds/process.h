using namespace std;

class Process{
  private:
    static unsigned int globalPID;
    int arrivalTime, totalCPUTime, cpuBurst, ioBurst, pid;
    int remainingTime;
  public:
    Process(int arrivalTime, int totalCPUTime, int cpuBurst, int ioBurst);
    int getPID();
};
