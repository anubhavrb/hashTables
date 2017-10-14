////////////////////////////////////////////////////////////////////////////////
//  hash.h
//  
//  Header file for hash table base class. Defines hash table behavior.
//  Anubhav Roy Bhattacharya, Harry Zhou, Collin Epstein
//
//  10/16/17
////////////////////////////////////////////////////////////////////////////////

#ifndef hashTable_h
#define hashTable_h

#include <stdio.h>
#include <string.h>
#include <math.h>

class HashTable{
  public:
    HashTable(int, double);
    ~HashTable();
    void printStatistics();
    int primaryHash(const string&);
    void hash(const string&);
    
  protected:
    virtual void initCollision(){} = 0;
    virtual void collisionHandler(){} = 0;

  private:
    int arrSize;
    int curIndex;
    string* table;
    int numHits;    // total # of search hits that occur on this table
    int numMisses;  // total # of search misses that occur on this table
    int numSuccess; // total # of probes on successful searches on this table
    int numFail;    // total # of probes on failed searches on this table
    
    int getNumHits();
    int getNumMisses();
    float getAvgOnSuccess();
    float getAvgOnFail();
    float getLoadFactor();
};

#endif /* hashTable_h */