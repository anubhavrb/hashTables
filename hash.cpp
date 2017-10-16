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
bool HashTable::hash(const string& s){
    
    int h = primaryHash(s);
    int offset = 0;
    int probes = 0;
    
    if (table[h].compare("") != 0) { // start collision handling if necessary
        initCollision(s);
        offset = collisionHandler();
        probes++;
        while(probes < arrSize && table[(h + offset) % arrSize] != ""){
            offset = collisionHandler();
            probes ++;
        }
    }
    if (probes < arrSize){
        table[(h + offset) % arrSize] = s; // store string
        return true;
    } else {
        return false;
    }
    
}

// search for entry in table
bool HashTable::search(const string& s) {
    
    int h = primaryHash(s);
    int probes = 0;
    
    // first probes at initial hash location
    if (table[h] == s){
        numHits++;
        numSuccess += probes + 1;
        return true;
    }
    else if (table[h] == ""){
        numMisses++;
        numFail += probes + 1;
        return false;
    }
    initCollision(s); // start collision handling if necessary
    int offset = collisionHandler();
    
    // find allowed location using collision handler
    while (probes < arrSize) { // limit search to size of hash table
        if (table[(h + offset) % arrSize] == s){
            numHits++;
            numSuccess += probes + 1;
            return true;
        }
        else if (table[(h + offset) % arrSize] == ""){
            numMisses++;
            numFail += probes + 1;
            return false;
        }
        offset = collisionHandler();
        numMisses++;
        probes++;
    }
    
    return false;
}

// getter for total # of search hits that occur on this table
int HashTable::getNumHits(){ return numHits; }

// getter for total # of search misses that occur on this table
int HashTable::getNumMisses(){ return numMisses; }

// calculates and returns total # of probes on successful searches on this table
float HashTable::getAvgOnSuccess(){
    return static_cast<float>(numSuccess) / numHits;
}

// calculates and returns total # of probes on failed searches on this table
float HashTable::getAvgOnFail(){
    return static_cast<float>(numFail) / numMisses;
}

// primary hash function. uses horner evaluation on string to create hash value
int HashTable::primaryHash(const string& s){
    
    int h = 0;
    const int b = 127;
    
    // Horner evaluation
    for(int i = 0 ; i < s.length(); i++) h = (b * h + s[i]) % arrSize;
    
    return h;
}




