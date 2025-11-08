#include "iostream"
#include <random>
#include "../include/algorithm.h"
#include "../include/utils.h"

Algorithm::Algorithm()
{
}

vector<Sack> Algorithm::populate()
{
    vector<Sack> initialPopulation;
    initialPopulation = randomPopulation();
    return initialPopulation;
}

pair<Sack, Sack> Algorithm::select(const vector<Sack> &population)
{
    pair<Sack, Sack> selectedSacks;
    selectedSacks = fitnessSelection(population);
    return selectedSacks;
}

Sack Algorithm::crossover(const pair<Sack, Sack> &parents)
{
    Sack childSack;
    childSack = orderedCrossover(parents);
    return childSack;
}

Sack Algorithm::mutate(Sack &sack)
{
    Sack mutatedSack;
    mutatedSack = inversionMutation(sack);
    return mutatedSack;
}