//
//  quadraticprobe.hpp
//  hashTables
//
//  Created by Zhou, Harry on 10/15/17.
//  Copyright © 2017 Roy Bhattacharya, Anubhav. All rights reserved.
//

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
