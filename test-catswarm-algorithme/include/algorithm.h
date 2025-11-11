#ifndef ALGORITHME_H
#define ALGORITHME_H

#include "utils.h"
#include <vector>
#include <random>
#include <algorithm>

class Algorithme
{
public:
    Algorithme();

    Cat seekingMode(Cat &cat);
    Cat tracingMode(Cat &cat);
};

#endif
