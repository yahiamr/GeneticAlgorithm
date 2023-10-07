#include <iostream>
#include <GA.h>

using Genome = char;   // Order of cities
using Fitness = double;            // Total distance

int main(){

auto fitnessFunction = [](const Genome& genome) -> Fitness {
        // Calculate the total distance of the path represented by genome
        // ...
        std::string target = "Hello world yaya";
        
        int fit=0;
        return fit;
    };

    GeneticAlgorithm<Genome,Fitness> ga(100,16);
    //ga.SetFitFunc(fitnessFunction);
    // for (size_t i = 0; i < 100; i++)
    // {
    ga.RunGeneration();
    // }
std::cout<<"Hello GA"<<std::endl;
    return 0;
}