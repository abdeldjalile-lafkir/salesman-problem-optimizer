#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "utils.h"
#include <vector>

class Algorithm
{
private:
public:
    Algorithm();

    vector<Sack> populate();
    pair<Sack, Sack> select(const vector<Sack> &population);
    Sack crossover(const pair<Sack, Sack> &parents);
    Sack mutate(Sack &sack);
};

#endif