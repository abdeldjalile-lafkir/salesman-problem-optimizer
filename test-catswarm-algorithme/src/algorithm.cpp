#include "iostream"
#include <random>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "../include/algorithm.h"
#include "../include/utils.h"

Algorithme::Algorithme()
{
}

Cat Algorithme::seekingMode(Cat &cat)
{
    vector<Cat> candidates;
    for (int i = 0; i < SMP; i++)
    {
        Cat candidate = cat;

        unordered_set<int> dimensionsToChange;
        while (int(dimensionsToChange.size()) < CDC)
        {
            int dim = rand() % dimensions;
            dimensionsToChange.insert(dim);
        }

        for (int dim : dimensionsToChange)
        {
            double change = ((double)rand() / RAND_MAX * 2 - 1) * SRD * candidate.positions[dim];
            candidate.positions[dim] += change;
        }
        candidate.fitness = fitness(candidate);
        candidates.push_back(candidate);
    }

    cat = probabilitySelection(cat, candidates);
    cat.fitness = fitness(cat);
    return cat;
}

Cat Algorithme::tracingMode(Cat &cat)
{
    for (int dim = 0; dim < dimensions; dim++)
    {
        double r1 = (double)rand() / RAND_MAX;
        cat.velocities[dim] = cat.velocities[dim] + r1 * learningRate * (bestCat.positions[dim] - cat.positions[dim]);
        cat.velocities[dim] = validateVelocity(cat.velocities[dim]);
        cat.positions[dim] += cat.velocities[dim];
    }
    cat.fitness = fitness(cat);
    return cat;
}