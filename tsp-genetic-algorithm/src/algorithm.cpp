#include "iostream"
#include <random>
#include <algorithm>
#include "../include/algorithm.h"
#include "../include/utils.h"
static std::mt19937 rang(std::random_device{}());

Algorithm::Algorithm()
{
}

vector<Path> Algorithm::populate()
{
    vector<Path> initialPopulation;
    initialPopulation = randomPopulation();
    return initialPopulation;
}

pair<Path, Path> Algorithm::select(const vector<Path> &population)
{
    pair<Path, Path> selectedPaths;
    selectedPaths = fitnessSelection(population);
    return selectedPaths;
}

Path Algorithm::crossover(const pair<Path, Path> &parents)
{
    Path childPath;
    childPath = orderedCrossover(parents);
    return childPath;
}

Path Algorithm::mutate(Path &path)
{
    Path mutatedPath;
    mutatedPath = inversionMutation(path);
    return mutatedPath;
}