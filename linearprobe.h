// CSC 321 Analysis of Algorithms
// Fall 2017 Mossinghoff

#ifndef linearprobe_h
#define linearprobe_h

#include "hash.h"

class LinearProbe : public HashTable {
  public:
    LinearProbe(int, double);
  protected:
    void initCollision();
    int collisionHandler();
  private:
    int v2;
};

#endif
