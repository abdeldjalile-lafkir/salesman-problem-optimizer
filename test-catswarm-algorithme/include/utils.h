
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

// Cat Swarm Optimization parameters
extern int SMP;    // Seeking Memory Pool
extern int CDC;    // Counts of Dimensions to Change
extern bool SPC;   // Self-Position Consideration (true = consider current position)
extern double MR;  // Mixture Ratio (percentage of seeking mode cats)
extern double SRD; // Seeking Range of the Selected Dimension (percentage)

// Additional parameters
extern int populationSize;
extern int dimensions;
extern int maxIterations;

// Fitness Ranges
extern double minFitness;
extern double maxFitness;

// Velocity Ranges
extern double minVelocity;
extern double maxVelocity;

// Learning rate
extern double learningRate;

// Cat structure
struct Cat
{
    int id;
    vector<double> positions;
    vector<double> velocities;
    double fitness;
    bool isSeeking;
};

/// Global best cat
extern Cat bestCat;

// Global cat population
extern vector<Cat> cats;

// utility functions
void initialize();
double fitness(Cat &cat);
double validateVelocity(double velocity);
Cat probabilitySelection(Cat &cat, vector<Cat> &candidates);

#endif