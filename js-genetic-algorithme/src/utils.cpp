#include <unordered_set>
#include <random>
#include <algorithm>
#include "../include/utils.h"

using namespace std;
static mt19937 rang(std::random_device{}());

int numJobs = 7;
int initialPopulationSize = 50;

vector<string> machines = {"M1", "M2", "M3", "M4", "M5"};
vector<Job> jobs = {
    {0, {{0, 3, "M1"}, {1, 2, "M2"}, {2, 2, "M3"}}},
    {1, {{0, 2, "M2"}, {1, 1, "M3"}, {2, 4, "M4"}, {3, 2, "M5"}}},
    {2, {{0, 4, "M1"}, {1, 3, "M4"}, {2, 2, "M5"}}},
    {3, {{0, 3, "M3"}, {1, 2, "M5"}, {2, 1, "M1"}, {3, 2, "M2"}}},
    {4, {{0, 2, "M4"}, {1, 4, "M2"}, {2, 3, "M3"}}},
    {5, {{0, 1, "M5"}, {1, 2, "M1"}}},
    {6, {{0, 3, "M2"}, {1, 3, "M3"}, {2, 2, "M5"}, {3, 1, "M1"}, {4, 2, "M4"}}}};

// utility functions
bool validateOrder(const Order &order)
{
    // one a job task appeare in position i on machine Mx, it should not appear in position j on machine My where j <= i , for eaxh x<y
}

Order fitness(Order &order)
{
    int cost = 0;
    for (const auto &m : {order.M1, order.M2, order.M3, order.M4, order.M5})
    {
        int machineCost = 0;
        for (const auto &job : m)
        {
            for (const auto &task : job.tasks)
            {
                if (task.machine == machines[&m - &order.M1])
                {
                    machineCost += task.time;
                }
            }
        }
        cost = max(cost, machineCost);
    }
    order.cost = cost;
    return order;
}

bool hasConverged(const vector<Order> &population)
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

vector<Order> expendPopulation(vector<Order> &population, Order &order)
{
    population.push_back(order);
    return population;
}

// genetic-algorithm functions
vector<Order> randomPopulation()
{
    vector<Order> initialPopulation;
    for (int i = 0; i < initialPopulationSize; i++)
    {
        Order newOrder;
        Order tempOrder = newOrder;
        newOrder = fitness(tempOrder);
        initialPopulation.push_back(newOrder);
    }
    return initialPopulation;
};
pair<Order, Order> fitnessSelection(const vector<Order> &population)
{
    double totalCosts = 0.0;
    for (const auto &order : population)
    {
        totalCosts += 1 / order.cost;
    }
    auto selectParent = [&]()
    {
        double random = (double)rand() / RAND_MAX * totalCosts;
        double acc = 0.0;
        for (const auto &order : population)
        {
            acc += 1.0 / order.cost;
            if (acc >= random)
                return order;
        }
        return population.back();
    };

    return {selectParent(), selectParent()};
};

Order orderedCrossover(const pair<Order, Order> &parents)
{
    Order childOrder;
    const Order &p1 = parents.first;
    const Order &p2 = parents.second;

    childOrder.M1.resize(machines.size());
    int start = rand() % machines.size();
    int end = rand() % machines.size();
    if (start > end)
        std::swap(start, end);

    return childOrder;
};
Order inversionMutation(Order &order)
{
    {

        int start = rand() % machines.size();
        int end = rand() % machines.size();
        if (start > end)
            std::swap(start, end);

        return order;
    };
}