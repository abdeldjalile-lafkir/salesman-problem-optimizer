# Cat Swarm - [problem] Solver

A C++ implementation of a cat swarm optimization algorithm to solve the [problem].

## Overview

## Requirements

- CMake 3.10+
- C++17 compiler (GCC, Clang )

## Build

```bash
cd [problem]-catswarm-algorithme
mkdir -p build && cd build
cmake ..
make
```

## Run

```bash
./[problem]-catswarm-algorithme
```

## How It Works

The algorithm uses:

- \*\*\*\*:
- \*\*\*\*:
- \*\*\*\*:
- \*\*\*\*:
- \*\*\*\*:

## Configuration

Edit `src/utils.cpp`:

```cpp

int SMP = 5;
int CDC = 6;
bool SPC = true;
double MR = 0.5;
double SRD = 0.1;

int populationSize = 100;
int dimensions = 10;
int maxIterations = 10;

double minVelocity = -10.0;
double maxVelocity = 10.0;

double learningRate = 0.01;

```

## Output Example

```
Cat 57: 49.13
Cat Position : [ 4.11968 0.540576 8.42553 4.98368 6.08664 6.77246 7.92604 1.72261 4.54496 4.00785  ]
Cat Velocity : [ 0.126551 0.0715905 -0.184906 -0.224983 -0.258931 -0.4172 -0.300145 -0.00716908 0.039979 -0.151925  ]
...
==========================================
Best Cat: 64
Best Cat Fitness: 29.299
Best Cat Position : [ 8.05447 1.91181 5.88953 0.561733 1.0229 1.58265 2.44349 1.37851 5.8728 0.581077  ]
Best Cat Velocity : [ -0.0392414 0.0211698 -0.021573 0.0273386 0.00836031 0.00989558 0.00200356 0.0168031 -0.01839 0.000553952  ]
```
