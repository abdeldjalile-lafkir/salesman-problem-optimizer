#include "iostream"
#include "algorithm.h"
#include "utils.h"
#include <random>
static std::mt19937 rang(std::random_device{}());

Algorithm::Algorithm()
{
}

vector<Sack> Algorithm::populate()
{
    vector<Sack> initialPopulation;

    for (int i = 0; i < initialPopulationSize; i++)
    {
        Sack newSack;
        Sack tempSack = newSack;
        newSack = fitness(tempSack);
        initialPopulation.push_back(newSack);
    }

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