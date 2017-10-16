// CSC 321 Analysis of Algorithms
// Fall 2017 Mossinghoff

#include "linearprobe.h"

LinearProbe::LinearProbe(int maxN, double load) : HashTable(maxN, load) {}

void LinearProbe::initCollision() {
    v2 = 0;
}

int LinearProbe::collisionHandler() {
    return ++v2;
}
