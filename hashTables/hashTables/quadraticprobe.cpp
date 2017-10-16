////////////////////////////////////////////////////////////////////////////////
// quadraticprobe.cpp
//
// CSC 321 Fall 2017 Mossinghoff
// Program 2: Nonundergraduate Zarathustrianism
//
// Implementation file for hash table using quadratic probing collision handling
// Implements hash table virtual base class.
// Anubhav Roy Bhattacharya, Harry Zhou, Collin Epstein
// 10/16/17
////////////////////////////////////////////////////////////////////////////////


#include "quadraticprobe.h"

QuadraticProbe::QuadraticProbe(int maxN, double load): HashTable(maxN, load){}

void QuadraticProbe::initCollision(const string& s) {
    counter = 0;
}

int QuadraticProbe::collisionHandler() {
    return pow((-1), counter) * pow(++counter, 2);
}
