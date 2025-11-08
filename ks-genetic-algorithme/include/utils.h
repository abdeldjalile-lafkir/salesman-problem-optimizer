#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

extern int numItems;
extern int initialPopulationSize;
extern float A;
extern float B;

struct Object
{
    int id;
    int weight;
    int value;
    int quantity;
};

struct Sack
{
    int weight;
    int value;
    float fitness;
    vector<Object> objects;
};

// utility functions
vector<Sack> seedData();
bool validateSack(const Sack &sack);
bool hasConverged(const vector<Sack> &population);
Sack fitness(const Sack &sack);
vector<Sack> expendPopulation(vector<Sack> &population, Sack &sack);

// genetic-algorithm functions
pair<Sack, Sack> fitnessSelection(const vector<Sack> &population);
Sack orderedCrossover(const pair<Sack, Sack> &parents);
Sack inversionMutation(Sack &path);

#endif