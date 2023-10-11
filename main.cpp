#include <iostream>
#include <GA.h>

using Genome = char;    // Order of cities
using Fitness = double; // Total distance

int main()
{

    auto fitnessFunction = [](const std::vector<Genome> &genome) -> Fitness
    {
        std::string target = "Helloo";
        Fitness score = 0;
        for (size_t i = 0; i < genome.size(); i++)
        {
            score += (target[i] == genome[i]);
        }
       //cout << score << endl;
        return score;
    };

    GeneticAlgorithm<Genome, Fitness> ga(1000, 6);
    ga.SetFitFunc(fitnessFunction);
  for (size_t i = 0; i < 10; i++)
  {
    ga.RunGeneration();
  }
   
  

    //std::cout << "Hello GA" << std::endl;
    return 0;
}