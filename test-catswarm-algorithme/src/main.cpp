#include <iostream>
#include "../include/algorithm.h"

int main()
{
    int iteration = 0;

    Algorithme catSwarmAlgorithm;
    initialize();

    do
    {
        for (auto &cat : cats)
        {
            cat = cat.isSeeking ? catSwarmAlgorithm.seekingMode(cat) : catSwarmAlgorithm.tracingMode(cat);
            cout << "Cat " << cat.id << ": " << cat.fitness << endl;
            cout << "Cat Position : [ ";
            for (const auto &position : cat.positions)
            {
                cout << position << " ";
            }
            cout << " ]" << endl;
            cout << "Cat Velocity : [ ";
            for (const auto &velocity : cat.velocities)
            {
                cout << velocity << " ";
            }
            cout << " ]" << endl;
            cout << "-----------------------------------------" << endl;
            bestCat = cat.fitness < bestCat.fitness ? cat : bestCat;
        }

        iteration++;
    } while (iteration < maxIterations);

    cout << "==========================================" << endl;
    cout << "Best Cat: " << bestCat.id << endl;
    cout << "Best Cat Fitness: " << bestCat.fitness << endl;
    cout << "Best Cat Position : [ ";
    for (const auto &position : bestCat.positions)
    {
        cout << position << " ";
    }
    cout << " ]" << endl;
    cout << "Best Cat Velocity : [ ";
    for (const auto &velocity : bestCat.velocities)
    {
        cout << velocity << " ";
    }
    cout << " ]" << endl;

    return 0;
}
