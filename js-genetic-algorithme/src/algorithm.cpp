#include "iostream"
#include <random>
#include "../include/algorithm.h"
#include "../include/utils.h"

Algorithm::Algorithm()
{
}

vector<Order> Algorithm::populate()
{
    vector<Order> initialPopulation;
    initialPopulation = randomPopulation();
    return initialPopulation;
}

pair<Order, Order> Algorithm::select(const vector<Order> &population)
{
    pair<Order, Order> selectedOrders;
    selectedOrders = fitnessSelection(population);
    return selectedOrders;
}

Order Algorithm::crossover(const pair<Order, Order> &parents)
{
    Order childOrder;
    childOrder = orderedCrossover(parents);
    return childOrder;
}

Order Algorithm::mutate(Order &order)
{
    Order mutatedOrder;
    mutatedOrder = inversionMutation(order);
    return mutatedOrder;
}