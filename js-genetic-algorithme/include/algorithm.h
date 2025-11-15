#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "utils.h"
#include <vector>

class Algorithm
{
private:
public:
    Algorithm();

    vector<Order> populate();
    pair<Order, Order> select(const vector<Order> &population);
    Order crossover(const pair<Order, Order> &parents);
    Order mutate(Order &order);
};

#endif