#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

extern int numNodes;
extern int initialPopulationSize;

struct Node
{
    int id;
    string name;
};

struct Edge
{
    string endpoints;
    double weight;
};

struct Path
{
    vector<Node> nodes;
    double cost;
};

extern vector<Node> nodes;
extern vector<Edge> edges;

// utility functions
bool validatePath(const Path &path);
bool hasConverged(const vector<Path> &population);
Path fitness(Path &path);
vector<Path> expendPopulation(vector<Path> &population, Path &path);

// genetic-algorithm functions
vector<Path> randomPopulation();
pair<Path, Path> fitnessSelection(const vector<Path> &population);
Path orderedCrossover(const pair<Path, Path> &parents);
Path inversionMutation(Path &path);

#endif