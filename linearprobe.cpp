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

LinearProbe::LinearProbe(int maxN, double load) : HashTable(maxN, load) {}

void LinearProbe::initCollision(const string& s) {
    v2 = 0;
}

int LinearProbe::collisionHandler() {
    return ++v2;
}
