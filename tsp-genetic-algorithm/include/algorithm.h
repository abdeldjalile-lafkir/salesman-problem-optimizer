#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "utils.h"
#include <vector>

class Algorithm
{
private:
public:
    Algorithm();

    vector<Path> populate();
    pair<Path, Path> select(const vector<Path> &population);
    Path crossover(const pair<Path, Path> &parents);
    Path mutate(Path &path);
};

#endif