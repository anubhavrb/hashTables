////////////////////////////////////////////////////////////////////////////////
// quadraticprobe.ch
//
// CSC 321 Fall 2017 Mossinghoff
// Program 2: Nonundergraduate Zarathustrianism
//
// Header file for hash table using quadratic probing collision handling.
// Implements hash table virtual base class.
// Anubhav Roy Bhattacharya, Harry Zhou, Collin Epstein
// 10/16/17
////////////////////////////////////////////////////////////////////////////////

#ifndef quadraticprobe_h
#define quadraticprobe_h

#include "hash.h"

class QuadraticProbe : public HashTable {
    public:
        QuadraticProbe(int, double);
    protected:
        void initCollision(const string&);
        int collisionHandler();
    private:
        int counter;
};

#endif /* quadraticprobe_h */
