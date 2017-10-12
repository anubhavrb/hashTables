// CSC 321 Analysis of Algorithms
// Fall 2017 Mossinghoff

#include "linearprobe.h"

LinearProbe::LinearProbe(int maxN, double load) : HashTable(maxN, load) {}

void LinearProbe::init_collision_hash(const string& s) {
    v2 = 0;
}

int LinearProbe::get_collision_hash() {
    return ++v2;
}
