////////////////////////////////////////////////////////////////////////////////
//  hash.cpp
//
//  Implementation file for hash table base class. Defines hash table behavior.
//  Anubhav Roy Bhattacharya, Harry Zhou, Collin Epstein
//
//  10/16/17
////////////////////////////////////////////////////////////////////////////////

#include "hash.h"

// constructor
HashTable::HashTable(int maxN, double load){
    
    // assign class variables
    curIndex = 0;
    numHits = 0;
    numMisses = 0;
    numSuccess = 0;
    numFail = 0;
    

    
    // initialize hash table array
    table = new string[maxN];
    for (int i = 0; i<arrSize; i++) table[i] = NULL;
}

// destructor
HashTable::~HashTable(){
    delete[] table;
}

// primary hash function. uses horner evaluation on string to create has value
int HashTable::primaryHash(const string& s){
    
    int h = 0;
    const int b = 127;
    
    // Horner evaluation
    for(int i = 0 ; i < s.length(); i++) h = (b * h + s[i]) % arrSize;
    
    return h;
}

// general hash function
void HashTable::hash(const string& s){
    initCollision();
    int h = primaryHash(s);
    int offset = 0;
    while(table[h + offset]!=NULL){
        offset = collisionHandler();
    }
    table[h + offset] = s;
}

// getter for number of search hits that occur on this talble
int HashTable::getNumHits(){
    return numHits;
}

// getter for number of search misses that occur on this table
int HashTable::getNumMisses(){
    return numMisses;
}

// getter for number of probes during successful searches on this table
float HashTable::getAvgOnSuccess(){
    return numSuccess;
}

// getter for number of probes during failed searches on this table
float HashTable::getAvgOnFail(){
    return numFail;
}

// calculates and returns actual load factor of table


