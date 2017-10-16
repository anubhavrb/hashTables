////////////////////////////////////////////////////////////////////////////////
// linearprobe.ch
//
// CSC 321 Fall 2017 Mossinghoff
// Program 2: Nonundergraduate Zarathustrianism
//
// Implementation file for hash table using linear probing collision handling.
// Implements hash table virtual base class. Adapted from supplied code.
// Anubhav Roy Bhattacharya, Harry Zhou, Collin Epstein
// 10/16/17
////////////////////////////////////////////////////////////////////////////////

#ifndef linearprobe_h
#define linearprobe_h

#include "hash.h"

class LinearProbe : public HashTable {
    
  public:
    LinearProbe(int, double);
    
  protected:
    void initCollision(const string&);
    int collisionHandler();
    
  private:
    
};

#endif
