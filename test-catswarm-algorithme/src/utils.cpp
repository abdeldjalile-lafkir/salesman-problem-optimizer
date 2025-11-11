#include <unordered_set>
#include <random>
#include <numeric>
#include <limits>
#include <vector>
#include <algorithm>
#include "../include/utils.h"

using namespace std;
static mt19937 rang(std::random_device{}());

int SMP = 5;
int CDC = 6;
bool SPC = true;
double MR = 0.5;
double SRD = 0.1;

int populationSize = 100;
int dimensions = 10;
int maxIterations = 10;

double minFitness = numeric_limits<double>::max();
double maxFitness = numeric_limits<double>::lowest();

double minVelocity = -10.0;
double maxVelocity = 10.0;

double learningRate = 0.01;

Cat bestCat;
vector<Cat> cats;

// utility functions
void initialize()
{
    cats.clear();
    for (int i = 0; i < populationSize; i++)
    {
        Cat newCat;
        newCat.id = i;
        newCat.positions.resize(dimensions);
        newCat.velocities.resize(dimensions);
        for (int dimension = 0; dimension < dimensions; dimension++)
        {
            newCat.positions[dimension] = ((double)rand() / RAND_MAX) * 10.0;
            newCat.velocities[dimension] = 0.0;
        }
        newCat.fitness = fitness(newCat);
        newCat.isSeeking = ((double)rand() / RAND_MAX) < MR;
        cats.push_back(newCat);
    }

    bestCat = cats[rand() % populationSize];
}

double fitness(Cat &cat)
{
    double fitness = 0.0;
    for (const auto &position : cat.positions)
    {
        fitness += position;
    }
    return fitness;
}

double validateVelocity(double velocity)
{
    if (velocity < minVelocity)
        return minVelocity;
    else if (velocity > maxVelocity)
        return maxVelocity;
    return velocity;
}

Cat probabilitySelection(Cat &cat, vector<Cat> &candidates)
{
    vector<double> selectionProbabilities;
    for (const auto &candidate : candidates)
    {
        double numerator = std::abs(candidate.fitness - cat.fitness);
        double probability = numerator / (maxFitness - minFitness);
        selectionProbabilities.push_back(probability);
    }

    auto maxElement = std::max_element(selectionProbabilities.begin(), selectionProbabilities.end());
    int selectedIndex = std::distance(selectionProbabilities.begin(), maxElement);
    return selectedIndex >= 0 ? candidates[selectedIndex] : cat;
}
