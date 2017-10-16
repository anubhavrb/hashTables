////////////////////////////////////////////////////////////////////////////////
// hash.cpp
//
// CSC 321 Fall 2017 Mossinghoff
// Program 2: Nonundergraduate Zarathustrianism
//
// Implementation file for hash table base class. Defines hash table behavior.
// Anubhav Roy Bhattacharya, Harry Zhou, Collin Epstein
// 10/16/17
////////////////////////////////////////////////////////////////////////////////

#include "hash.h"

// constructor
HashTable::HashTable(int maxN, double load){
    
    // assign class variables
    numHits = 0;
    numMisses = 0;
    numSuccess = 0;
    numFail = 0;
    arrSize = maxN;
    
    // initialize hash table array
    table = new string[arrSize];
    
    for (int i = 0; i< arrSize; i++) table[i] = ""; // intialize empty array
}

// destructor
HashTable::~HashTable(){
    delete[] table;
}

// general hash function
void HashTable::hash(const string& s){
    
    int h = primaryHash(s);
    int offset = 0;
    
    if (table[h].compare("") != 0) { // start collision handling if necessary
        initCollision(s);
        offset = collisionHandler();
        while(table[(h + offset) % arrSize] != ""){
            offset = collisionHandler();
        }
    }
    
    table[(h + offset) % arrSize] = s; // store string
}

// search for entry in table
bool HashTable::search(const string& s) {
    
    int h = primaryHash(s);
    if (table[h] == s) return true;
    else if (table[h] == "") return false;
    initCollision(s); // start collision handling if necessary
    int offset = collisionHandler();
    
    int iterations = 0;
    while (iterations < arrSize) { // limit search to size of hash table
        if (table[(h + offset) % arrSize] == s) return true;
        else if (table[(h + offset) % arrSize] == "") return false;
        offset = collisionHandler();
        iterations++;
    }
    return false;
}

// primary hash function. uses horner evaluation on string to create hash value
int HashTable::primaryHash(const string& s){
    
    int h = 0;
    const int b = 127;
    
    // Horner evaluation
    for(int i = 0 ; i < s.length(); i++) h = (b * h + s[i]) % arrSize;
    
    return h;
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




