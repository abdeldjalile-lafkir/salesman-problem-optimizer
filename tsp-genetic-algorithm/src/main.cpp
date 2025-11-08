#include <iostream>
#include "../include/algorithm.h"

int main()
{
  int generations = 0;

  Algorithm geneticAlgorithm;
  vector<Node> nodes;
  vector<Edge> edges;
  vector<Path> population;

  pair<Path, Path> parents;
  Path path;
  bool status;

  Path optimumPath;
  optimumPath.cost = 100;

  population = geneticAlgorithm.populate();

  do
  {
    parents = geneticAlgorithm.select(population);
    path = geneticAlgorithm.crossover(parents);
    path = geneticAlgorithm.mutate(path);

    status = validatePath(path);
    if (!status)
    {
      cerr << "Invalid path generated." << endl;
      continue;
    }

    Path tempPath = path;
    path = fitness(tempPath);

    population = expendPopulation(population, path);

    cout << "Path: [";
    for (const auto &node : path.nodes)
    {
      cout << " " << node.name << " ";
    }
    cout << "]" << endl;
    cout << "Path cost = " << path.cost << endl;
    cout << "------------------------------------------" << endl;

    optimumPath = path.cost < optimumPath.cost ? path : optimumPath;
    generations++;

  } while (generations <= 100 && !hasConverged(population));

  cout << "==========================================" << endl;
  cout << "Optimum Path: [";
  for (const auto &node : optimumPath.nodes)
  {
    cout << " " << node.name << " ";
  }
  cout << "]" << endl;
  cout << "Path cost = " << optimumPath.cost << endl;

  return 0;
}
