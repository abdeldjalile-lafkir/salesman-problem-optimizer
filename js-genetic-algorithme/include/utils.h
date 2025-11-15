#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

extern int numJobs;
extern int initialPopulationSize;

struct Task
{
    int id;
    int time;
    string machine;
};

struct Job
{
    int id;
    vector<Task> tasks;
};

struct Order
{
    vector<Job> M1;
    vector<Job> M2;
    vector<Job> M3;
    vector<Job> M4;
    vector<Job> M5;
    double cost;
};

extern vector<string> machines;
extern vector<Job> jobs;

// utility functions
bool validateOrder(const Order &order);
bool hasConverged(const vector<Order> &population);
Order fitness(Order &order);
vector<Order> expendPopulation(vector<Order> &population, Order &order);

// genetic-algorithm functions
vector<Order> randomPopulation();
pair<Order, Order> fitnessSelection(const vector<Order> &population);
Order orderedCrossover(const pair<Order, Order> &parents);
Order inversionMutation(Order &order);

#endif