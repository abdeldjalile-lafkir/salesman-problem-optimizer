# Genetic Algorithm - JS Solver

A C++ implementation of a genetic algorithm to solve the Job Scheduling Problem.

## Overview

This program finds the optimal job sequence that minimizes the total completion time using evolutionary computing techniques.

## Requirements

- CMake 3.10+
- C++17 compiler (GCC, Clang )

## Build

```bash
cd js-genetic-algorithm
mkdir -p build && cd build
cmake ..
make
```

## Run

```bash
./js-genetic-algorithm
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

```

## Output Example

```

...
==========================================

```
