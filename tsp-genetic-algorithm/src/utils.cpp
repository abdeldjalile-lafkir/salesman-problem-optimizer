#include "utils.h"
#include <unordered_set>

using namespace std;

int numNodes = 7;
int initialPopulationSize = 50;

// utility functions
pair<vector<Node>, vector<Edge>> seedData(vector<Node> &nodes, vector<Edge> &edges)
{
    Node node;
    Edge edge;

    vector<string> names = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

    for (int i = 0; i < numNodes; i++)
    {
        node.id = i;
        node.name = names[i];
        nodes.push_back(node);
    }

    for (int i = 0; i < numNodes; i++)
    {
        for (int j = i + 1; j < numNodes; j++)
        {
            edge.endpoints = names[i] + names[j];
            edge.weight = 4 + rand() % (19 - 4 + 1);
            edges.push_back(edge);
        }
    }

    return {nodes, edges};
}

bool validatePath(const Path &path)
{
    if (path.nodes.empty())
        return false;
    if (path.nodes.size() != numNodes)
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

Path fitness(const vector<Edge> &edges, Path &path)
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