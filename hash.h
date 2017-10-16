////////////////////////////////////////////////////////////////////////////////
// hash.h
//
// CSC 321 Fall 2017 Mossinghoff
// Program 2: Nonundergraduate Zarathustrianism
//
// Header file for hash table base class. Defines hash table behavior.
// Anubhav Roy Bhattacharya, Harry Zhou, Collin Epstein
// 10/16/17
////////////////////////////////////////////////////////////////////////////////

#ifndef hashTable_h
#define hashTable_h

#include <stdio.h>
#include <string>
#include <math.h>

using namespace std;

class HashTable{
  public:
    HashTable(int, double);
    ~HashTable();
    void hash(const string&);
    bool search(const string&);
    void printStatistics();
    
  protected:
    int arrSize;
    int primaryHash(const string&);
    virtual void initCollision(const string&) = 0;
    virtual int collisionHandler() = 0;
    int counter;

  private:
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
