#include <iostream>
#include <GA.h>

using Genome = char;    // Order of cities
using Fitness = double; // Total distance

int main()
{
int dnaLength = 0;
std::string target = "To be or not to be that's not the question";
dnaLength = target.size();
int glb_score = 0;
  auto fitnessFunction = [&target,&glb_score](const std::vector<Genome> &genome) -> Fitness
  {
    Fitness score = 0;
    for (size_t i = 0; i < genome.size(); i++)
    {
      score += (target[i] == genome[i]);
    }
    // cout << score << endl;
    glb_score = score;
    return score;
  };

  GeneticAlgorithm<Genome, Fitness> ga(300, dnaLength);
  ga.SetFitFunc(fitnessFunction);
  int count = 0;
  while(glb_score != dnaLength)
  {
    ga.RunGeneration();
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << count++ << "================================" << endl;
  }

  // std::cout << "Hello GA" << std::endl;
  return 0;
}