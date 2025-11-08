#include <unordered_set>
#include <random>
#include <algorithm>
#include "../include/utils.h"

using namespace std;
static mt19937 rang(std::random_device{}());

int numItems = 12;
int initialPopulationSize = 50;

float A = 0.5;
float B = 0.5;

vector<Object> objects = {
    {0, 2, 20, 1},
    {1, 3, 40, 2},
    {2, 1, 20, 2},
    {3, 4, 30, 2},
    {4, 2, 10, 1},
    {5, 3, 50, 2},
    {6, 1, 20, 1},
    {7, 4, 30, 3},
    {8, 2, 18, 2},
    {9, 3, 22, 1},
    {10, 4, 24, 1},
    {11, 1, 30, 1}};

// utility functions
bool validateSack(const Sack &sack)
{
    if (sack.objects.empty() || sack.objects.size() < 8 || sack.weight > 100)
        return "Invalid sack";

    unordered_set<int> seen;
    for (const auto &object : sack.objects)
    {
        if (seen.count(object.id) == 0)
        {
            seen.insert(object.id);
        }
    }

    return seen.size() >= 8 ? true : false;
}

Sack fitness(Sack &sack)
{
    int totalWeight = 0;
    int totalValue = 0;
    for (const auto &object : sack.objects)
    {
        totalWeight += object.weight * object.quantity;
        totalValue += object.value * object.quantity;
    }

    sack.weight = totalWeight;
    sack.value = totalValue;
    sack.fitness = A * totalWeight + B * totalValue;
    return sack;
}

bool hasConverged(const vector<Sack> &population)
{
    if (population.size() < 10)
        return false;

    double different = 1.0;
    double firstFitness = population.back().fitness;
    size_t startIdx = population.size() - 10;
    for (size_t i = startIdx; i < population.size(); ++i)
    {
        if (abs(population[i].fitness - firstFitness) > different)
            return false;
    }
    return true;
}

vector<Sack> expendPopulation(vector<Sack> &population, Sack &sack)
{
    population.push_back(sack);
    return population;
}

// genetic-algorithm functions
vector<Sack> randomPopulation()
{
    vector<Sack> initialPopulation;
    vector<Object> availableObjects = objects;

    for (int i = 0; i < initialPopulationSize; i++)
    {
        Sack newSack;
        shuffle(availableObjects.begin(), availableObjects.end(), rang);
        newSack.objects.clear();
        newSack.objects.reserve(numItems);
        newSack.objects = vector<Object>(availableObjects.begin(), availableObjects.begin() + 8 + rand() % (numItems - 8));
        newSack = fitness(newSack);
        initialPopulation.push_back(newSack);
    }

    return initialPopulation;
}
pair<Sack, Sack> fitnessSelection(const vector<Sack> &population)
{
    double totalFitness = 0.0;
    for (const auto &sack : population)
    {
        totalFitness += sack.fitness;
    }
    auto selectParent = [&]()
    {
        double random = (double)rand() / RAND_MAX * totalFitness;
        double acc = 0.0;
        for (const auto &sack : population)
        {
            acc += sack.fitness;
            if (acc >= random)
                return sack;
        }
        return population.back();
    };

    return {selectParent(), selectParent()};
};

Sack orderedCrossover(const pair<Sack, Sack> &parents)
{
    Sack childSack;
    const Sack &s1 = parents.first;
    const Sack &s2 = parents.second;

    childSack.objects.resize(s1.objects.size());
    int start = rand() % s1.objects.size();
    int end = rand() % s1.objects.size();
    if (start > end)
        std::swap(start, end);

    unordered_set<int> selected;
    for (int i = start; i <= end; i++)
    {
        childSack.objects[i] = s1.objects[i];
        selected.insert(s1.objects[i].id);
    }

    int idx = (end + 1) % s1.objects.size();
    for (int i = 0; i < int(s2.objects.size()); i++)
    {
        const Object &object = s2.objects[i];
        if (selected.count(object.id) == 0)
        {
            if (idx < static_cast<int>(childSack.objects.size()))
            {
                childSack.objects[idx] = object;
                idx = (idx + 1) % s1.objects.size();
            }
        }
    }
    return childSack;
};
Sack inversionMutation(Sack &sack)
{
    unordered_set<int> objectIds;
    for (const auto &obj : sack.objects)
    {
        objectIds.insert(obj.id);
    }

    if (sack.objects.size() <= 9)
    {
        vector<Object> availableObjects;
        for (const auto &obj : objects)
        {
            if (objectIds.count(obj.id) == 0)
            {
                sack.objects.push_back(obj);
            }
        }
    }
    else if (sack.objects.size() >= 11)
    {
        sack.objects.pop_back();
    }
    else
    {
        int idx = rand() % sack.objects.size();
        if (sack.objects[idx].quantity < objects[objects[idx].id].quantity)
        {
            sack.objects[idx].quantity += 1;
        }
    }
    return sack;
}