////////////////////////////////////////////////////////////////////////////////
// doublehash.cpp
//
// CSC 321 Fall 2017 Mossinghoff
// Program 2: Nonundergraduate Zarathustrianism
//
// Implementation file for hash table using double hashing collision handling.
// Implements hash table virtual base class.
// Anubhav Roy Bhattacharya, Harry Zhou, Collin Epstein
// 10/16/17
////////////////////////////////////////////////////////////////////////////////

#include "doublehash.h"

// constructor - call base class constructor
DoubleHash::DoubleHash(int maxN): HashTable(maxN){}

// collision handler initialization
void DoubleHash::initCollision(const string& s) {
    counter = 0;        // reset counter
    hashVal = h2(s);    // evaluate secondary hashing
}

// collision handler - determines which table slot to probe next
int DoubleHash::collisionHandler() {
    return (++counter) * hashVal;
}

// secondary hash function for use with double hashing collision handling
// uses Horner evaluation with different base. may not return value 0.
int DoubleHash::h2(const string& s){
    
    int h = 0;
    const int b = 23; // different prime base - cannot be 127
    
    // Horner evaluation
    for(int i = 0 ; i < s.length(); i++) h = (b * h + s[i]) % arrSize;
    /*if (h < 1){
        h += s.length(); // may not return 0. assumes word length < 127 letters
    }*/
    return h;
}
