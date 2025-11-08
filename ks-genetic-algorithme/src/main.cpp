#include <iostream>
#include "../include/algorithm.h"

int main()
{
  int generations = 0;

  Algorithm geneticAlgorithm;
  vector<Sack> population;

  pair<Sack, Sack> parents;
  Sack sack;
  bool status;

  Sack optimumSack;
  optimumSack.fitness = 0.0;

  population = geneticAlgorithm.populate();

  do
  {
    parents = geneticAlgorithm.select(population);
    sack = geneticAlgorithm.crossover(parents);
    sack = geneticAlgorithm.mutate(sack);

    Sack tempSack = sack;
    sack = fitness(tempSack);

    status = validateSack(sack);
    if (!status)
    {
      cerr << "Invalid sack generated." << endl;
      continue;
    }

    population = expendPopulation(population, sack);

    cout << "Sack: [";
    for (const auto &object : sack.objects)
    {
      cout << " " << object.id << " ";
    }
    cout << "]" << endl;
    cout << "Sack weight = " << sack.weight << endl;
    cout << "Sack value = " << sack.value << endl;
    cout << "Sack fitness = " << sack.fitness << endl;
    cout << "-----------------------------------------------------------------" << endl;

    optimumSack = sack.fitness > optimumSack.fitness ? sack : optimumSack;
    generations++;

  } while (generations <= 100 && !hasConverged(population));

  cout << "==========================================" << endl;
  cout << "Optimum Sack: [";
  for (const auto &object : optimumSack.objects)
  {
    cout << " " << object.id << " ";
  }
  cout << "]" << endl;
  cout << "Sack weight = " << optimumSack.weight << endl;
  cout << "Sack value = " << optimumSack.value << endl;
  cout << "Sack fitness = " << optimumSack.fitness << endl;

  return 0;
}
