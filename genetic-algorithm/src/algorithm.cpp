#include "iostream"
#include "algorithm.h"
#include <algorithm>
#include "utils.h"
#include <random>
static std::mt19937 rang(std::random_device{}());

Algorithm::Algorithm()
{
}

vector<Path> Algorithm::populate(const vector<Node> &nodes, const vector<Edge> &edges)
{
    vector<Path> initialPopulation;

    for (int i = 0; i < initialPopulationSize; i++)
    {
        Path newPath;
        newPath.nodes = nodes;
        shuffle(newPath.nodes.begin(), newPath.nodes.end(), rang);
        Path tempPath = newPath;
        newPath = fitness(edges, tempPath);
        initialPopulation.push_back(newPath);
    }

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