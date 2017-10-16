////////////////////////////////////////////////////////////////////////////////
// doublehash.c
//
// CSC 321 Fall 2017 Mossinghoff
// Program 2: Nonundergraduate Zarathustrianism
//
// Header file for hash table using double hashing collision handling.
// Implements hash table virtual base class.
// Anubhav Roy Bhattacharya, Harry Zhou, Collin Epstein
// 10/16/17
////////////////////////////////////////////////////////////////////////////////

#ifndef doublehash_h
#define doublehash_h

#include "hash.h"

class DoubleHash : public HashTable {
    
  public:
    DoubleHash(int, double);
    
  protected:
    void initCollision(const string&);
    int collisionHandler();
    
  private:
    int hashVal;
    int h2(const string&);
};

#endif /* doublehash_h */
