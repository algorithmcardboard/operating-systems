#ifndef PTE_H
#define PTE_H

struct pte{
  unsigned int present:1;
  unsigned int modified:1;
  unsigned int referenced:1;
  unsigned int paged_out:1;
  unsigned int frame_number:6;
};

#endif
