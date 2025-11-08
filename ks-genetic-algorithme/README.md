# Genetic Algorithm - Knapsack Solver

A C++ implementation of a genetic algorithm to solve the knapsack Problem.

## Overview

This program solves the knapsack problem using evolutionary computing techniques.

## Requirements

- CMake 3.10+
- C++17 compiler (GCC, Clang )

## Build

```bash
cd ks-genetic-algorithm
mkdir -p build && cd build
cmake ..
make
```

## Run

```bash
./ks-genetic-algorithm
```

## How It Works

The algorithm uses:

- **Selection**: Fitness-based parent selection
- **Crossover**: Ordered crossover (OX)
- **Mutation**: Inversion mutation
- **Termination**: 100 generations or convergence

## Configuration

Edit `src/utils.cpp`:

```cpp
int numItems = 12;
int initialPopulationSize = 50;
float A = 0.5; // alpha value for multiplying weight
float B = 0.5; // beta value for multiplying value
```

## Output Example

```
Sack: [ 0 3 4 2 1 6 5 ]
Sack weight = 87
Sack value = 120
Sack fitness = 84
...
==========================================
Optimum Sack: [ 0 2 3 1 5 4 ]
Sack weight = 79
Sack value = 100
Sack fitness = 80
```
