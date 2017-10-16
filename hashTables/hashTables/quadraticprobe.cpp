//
//  quadraticprobe.cpp
//  hashTables
//
//  Created by Zhou, Harry on 10/15/17.
//  Copyright © 2017 Roy Bhattacharya, Anubhav. All rights reserved.
//

#include "quadraticprobe.h"

QuadraticProbe::QuadraticProbe(int maxN, double load): HashTable(maxN, load){}

void QuadraticProbe::initCollision(const string& s) {
    counter = 0;
}

int QuadraticProbe::collisionHandler() {
    return pow((-1), counter) * pow(++counter, 2);
}
