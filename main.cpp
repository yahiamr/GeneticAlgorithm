#include <iostream>
#include <GA.h>

using Genome = char;   // Order of cities
using Fitness = double;            // Total distance

int main(){

auto fitnessFunction = [](const Genome& genome) -> Fitness {
        // Calculate the total distance of the path represented by genome
        // ...
        int fit=0;
        return fit;
    };

    GeneticAlgorithm<Genome,Fitness> ga(100,20);

std::cout<<"Hello GA"<<std::endl;
    return 0;
}