#include <unordered_set>
#include <random>
#include <algorithm>
#include "../include/utils.h"

using namespace std;
static mt19937 rang(std::random_device{}());

int numNodes = 7;
int initialPopulationSize = 50;

vector<Node> nodes = {{0, "A"}, {1, "B"}, {2, "C"}, {3, "D"}, {4, "E"}, {5, "F"}, {6, "G"}, {7, "H"}, {8, "I"}, {9, "J"}, {10, "K"}, {11, "L"}, {12, "M"}, {13, "N"}, {14, "O"}, {15, "P"}, {16, "Q"}, {17, "R"}, {18, "S"}, {19, "T"}, {20, "U"}, {21, "V"}, {22, "W"}, {23, "X"}, {24, "Y"}, {25, "Z"}};
vector<Edge> edges = {
    {"AB", 10}, {"AC", 15}, {"AD", 20}, {"AE", 18}, {"AF", 12}, {"AG", 16}, {"BC", 12}, {"BD", 18}, {"BE", 14}, {"BF", 9}, {"BG", 17}, {"CD", 14}, {"CE", 19}, {"CF", 11}, {"CG", 13}, {"DE", 16}, {"DF", 20}, {"DG", 8}, {"EF", 17}, {"EG", 15}, {"FG", 11}};

// utility functions
bool validatePath(const Path &path)
{
    if (path.nodes.empty())
        return false;
    if (int(path.nodes.size()) != numNodes)
        return false;

    vector<string> seen;
    for (const auto &node : path.nodes)
    {
        if (node.name.empty())
            return false;
        for (const auto &s : seen)
            if (s == node.name)
                return false;
        seen.push_back(node.name);
    }

    return true;
}

Path fitness(Path &path)
{
    string endpoints = "";
    int cost = 0;
    for (int i = 0; i < numNodes; i++)
    {
        endpoints = path.nodes[i].name + path.nodes[(i + 1) % numNodes].name;
        for (const auto &edge : edges)
        {
            if (edge.endpoints == endpoints || edge.endpoints == string{endpoints[1], endpoints[0]})
            {
                cost += edge.weight;
                break;
            }
        }
    }

    path.cost = cost;
    return path;
}

bool hasConverged(const vector<Path> &population)
{
    if (population.size() < 10)
        return false;

    double different = 1.0;
    double firstCost = population.back().cost;
    size_t startIdx = population.size() - 10;
    for (size_t i = startIdx; i < population.size(); ++i)
    {
        if (abs(population[i].cost - firstCost) > different)
            return false;
    }
    return true;
}

vector<Path> expendPopulation(vector<Path> &population, Path &path)
{
    population.push_back(path);
    return population;
}

// genetic-algorithm functions
vector<Path> randomPopulation()
{
    vector<Path> initialPopulation;
    for (int i = 0; i < initialPopulationSize; i++)
    {
        Path newPath;
        newPath.nodes = vector<Node>(nodes.begin(), nodes.begin() + numNodes);
        shuffle(newPath.nodes.begin(), newPath.nodes.end(), rang);
        Path tempPath = newPath;
        newPath = fitness(tempPath);
        initialPopulation.push_back(newPath);
    }
    return initialPopulation;
};
pair<Path, Path> fitnessSelection(const vector<Path> &population)
{
    double totalCosts = 0.0;
    for (const auto &path : population)
    {
        totalCosts += 1 / path.cost;
    }
    auto selectParent = [&]()
    {
        double random = (double)rand() / RAND_MAX * totalCosts;
        double acc = 0.0;
        for (const auto &path : population)
        {
            acc += 1.0 / path.cost;
            if (acc >= random)
                return path;
        }
        return population.back();
    };

    return {selectParent(), selectParent()};
};

Path orderedCrossover(const pair<Path, Path> &parents)
{
    Path childPath;
    const Path &p1 = parents.first;
    const Path &p2 = parents.second;

    childPath.nodes.resize(numNodes);
    int start = rand() % numNodes;
    int end = rand() % numNodes;
    if (start > end)
        std::swap(start, end);

    unordered_set<string> selected;
    for (int i = start; i <= end; i++)
    {
        childPath.nodes[i] = p1.nodes[i];
        selected.insert(p1.nodes[i].name);
    }

    int idx = (end + 1) % numNodes;
    for (int i = 0; i < numNodes; i++)
    {
        const Node &node = p2.nodes[i];
        if (selected.count(node.name) == 0)
        {
            childPath.nodes[idx] = node;
            idx = (idx + 1) % numNodes;
        }
    }
    return childPath;
};
Path inversionMutation(Path &path)
{
    {

        int start = rand() % numNodes;
        int end = rand() % numNodes;
        if (start > end)
            std::swap(start, end);

        while (start < end)
        {
            std::swap(path.nodes[start], path.nodes[end]);
            start++;
            end--;
        }

        path.cost = 0.0;
        return path;
    };
}