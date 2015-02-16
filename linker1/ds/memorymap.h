#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

class MemoryMap{
  public:
    static MemoryMap& getInstance(){
      static MemoryMap instance;
      return instance;
    }
  private:
    MemoryMap(){ }

    MemoryMap(MemoryMap const&);
    void operator=(MemoryMap const&);
};

#endif
