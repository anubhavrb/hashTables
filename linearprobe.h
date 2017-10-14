// CSC 321 Analysis of Algorithms
// Fall 2017 Mossinghoff

#ifndef linearprobe_h
#define linearprobe_h

#include "hash.h"

class LinearProbe : public HashTable {
  public:
    LinearProbe(int, double);
  protected:
    void init_collision_hash(const string&);
    int get_collision_hash();
  private:
    int v2;
};

#endif
