#include "utils.h"
#include <unordered_set>

using namespace std;

int numNodes = 7;
int maxWeight = 30;
int initialPopulationSize = 50;
float A = 1.0;
float B = 0.5;

// utility functions
void seedData()
{
}

bool validateSack(const Sack &sack)
{
    if (sack.objects.empty())
        return false;
    if (sack.weight > maxWeight)
        return false;

    unordered_set<string> seen;
    for (const auto &object : sack.objects)
    {
        if (seen.count(object.id) == 0)
        {
            seen.insert(object.id);
        }
    }

    return seen.size() >= 8 ? true : false;
}

Sack fitness(const Sack &sack)
{
    int totalWeight = 0;
    int totalValue = 0;
    for (const auto &object : sack.objects)
    {
        totalWeight += object.weight;
        totalValue += object.value;
    }

    sack.weight = totalWeight;
    sack.value = totalValue;
    sack.fitness = totalValue * A - totalWeight * B;
    return sack;
}

bool hasConverged(const vector<Sack> &population)
{
    if (population.empty())
        return false;

    double different = 1;
    double first = population[0].fitness;
    for (const auto &sack : population)
    {
        if (abs(sack.fitness - first) > different)
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

// TODO: Implement these functions later
// pair<Path, Path> elitismTournamentSelection(const vector<Path> &population) {};
// Path edgeRecombinationCrossover(const pair<Path, Path> &parents) {};
// Path twoOptMutation(Path &path) {};