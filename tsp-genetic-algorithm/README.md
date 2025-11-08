# Genetic Algorithm - TSP Solver

A C++ implementation of a genetic algorithm to solve the Traveling Salesman Problem.

## Overview

This program finds the shortest route that visits all cities exactly once and returns to the starting city using evolutionary computing techniques.

## Requirements

- CMake 3.10+
- C++17 compiler (GCC, Clang )

## Build

```bash
cd tsp-genetic-algorithm
mkdir -p build && cd build
cmake ..
make
```

## Run

```bash
./tsp-genetic-algorithm
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
int numNodes = 7;
int initialPopulationSize = 50;
```

## Output Example

```
Path: [ A  C  B  E  D  F  G  ]
Path cost = 87
...
==========================================
Optimum Path: [ A  E  C  D  B  G  F  ]
Path cost = 79
```
