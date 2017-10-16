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

DoubleHash::DoubleHash(int maxN, double load): HashTable(maxN, load){}

void DoubleHash::initCollision(const string& s) {
    counter = 0;
    v2 = h2(s);
}

int DoubleHash::h2(const string& s){
    int h = 0;
    const int b = 23;
    
    // Horner evaluation
    for(int i = 0 ; i < s.length(); i++) h = (b * h + s[i]) % arrSize;
    if (h < 1){
        h += s.length();
    }
    return h;
}

int DoubleHash::collisionHandler() {
    return (++counter)*v2;
}
