//
//  doublehash.hpp
//  hashTables
//
//  Created by Zhou, Harry on 10/15/17.
//  Copyright © 2017 Roy Bhattacharya, Anubhav. All rights reserved.
//

#ifndef doublehash_h
#define doublehash_h

#include "hash.h"

class DoubleHash : public HashTable {
public:
    DoubleHash(int, double);
protected:
    void initCollision(const string&);
    int collisionHandler();
private:
    int counter;
    int v2;
    int h2(const string&);
};

#endif /* doublehash_h */
