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

// utility functions
pair<vector<Node>, vector<Edge>> seedData(vector<Node> &nodes, vector<Edge> &edges);
bool validatePath(const Path &path);
bool hasConverged(const vector<Path> &population);
Path fitness(const vector<Edge> &edges, Path &path);
vector<Path> expendPopulation(vector<Path> &population, Path &path);

// genetic-algorithm functions
pair<Path, Path> fitnessSelection(const vector<Path> &population);
Path orderedCrossover(const pair<Path, Path> &parents);
Path inversionMutation(Path &path);

#endif