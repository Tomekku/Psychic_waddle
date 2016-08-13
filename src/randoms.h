#ifndef RANDOMS_H
#define RANDOMS_H

#include <time.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "block.h"
#include "randoms.h"
#include "mazegenerator.h"

class Randoms {

public:
    Randoms();
    Randoms(int);
    ~Randoms(){}
    int getNum();
    bool haveNumbers();
private:
    std::vector<int> _numbers;
};
#endif // RANDOMS_H
