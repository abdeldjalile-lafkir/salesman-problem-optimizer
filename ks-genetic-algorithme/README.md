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
int numItems = 10;
int initialPopulationSize = 50;
```

## Output Example

```

```
