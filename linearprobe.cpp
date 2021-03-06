////////////////////////////////////////////////////////////////////////////////
// linearprobe.cpp
//
// CSC 321 Fall 2017 Mossinghoff
// Program 2: Nonundergraduate Zarathustrianism
//
// Implementation file for hash table using linear probing collision handling.
// Implements hash table virtual base class. Adapted from supplied code.
// Anubhav Roy Bhattacharya, Harry Zhou, Collin Epstein
// 10/16/17
////////////////////////////////////////////////////////////////////////////////

#include "linearprobe.h"

// constructor - call base class constructor
LinearProbe::LinearProbe(int maxN) : HashTable(maxN) {}

// collision handler initialization
void LinearProbe::initCollision(const string& s) {
    counter = 0; // reset counter
}

// collision handler - determines which table slot to probe next
int LinearProbe::collisionHandler() {
    return ++counter;
}
