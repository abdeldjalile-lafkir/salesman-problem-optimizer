#include <iostream>
#include "../include/algorithm.h"

int main()
{
  int generations = 0;

  Algorithm geneticAlgorithm;
  vector<Order> population;

  pair<Order, Order> parents;
  Order order;
  bool status;

  Order optimumOrder;
  optimumOrder.cost = 100;

  population = geneticAlgorithm.populate();

  do
  {
    parents = geneticAlgorithm.select(population);
    order = geneticAlgorithm.crossover(parents);
    order = geneticAlgorithm.mutate(order);

    Order tempOrder = order;
    order = fitness(tempOrder);

    status = validateOrder(order);
    if (!status)
    {
      cerr << "Invalid order generated." << endl;
      continue;
    }

    population = expendPopulation(population, order);

    cout << "Order: [" << endl;
    for (const auto &m : {order.M1, order.M2, order.M3, order.M4, order.M5})
    {
      cout << "Machine " << &m - &order.M1 + 1 << ": [ ";
      for (const auto &job : m)
      {
        cout << " " << job.id << " ";
      }
      cout << "]" << endl;
    }
    cout << "]" << endl;
    cout << "Order cost = " << order.cost << endl;
    cout << "------------------------------------------" << endl;

    optimumOrder = order.cost < optimumOrder.cost ? order : optimumOrder;
    generations++;

  } while (generations <= 100 && !hasConverged(population));

  cout << "==========================================" << endl;
  cout << "Optimum Order: [" << endl;
  for (const auto &m : {optimumOrder.M1, optimumOrder.M2, optimumOrder.M3, optimumOrder.M4, optimumOrder.M5})
  {
    cout << "Machine " << &m - &optimumOrder.M1 + 1 << ": [ ";
    for (const auto &job : m)
    {
      cout << " " << job.id << " ";
    }
    cout << "]" << endl;
  }
  cout << "]" << endl;
  cout << "Order cost = " << optimumOrder.cost << endl;

  return 0;
}
