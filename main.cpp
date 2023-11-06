#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <unordered_map>
#include <GA.h>
#include <helpers.hpp>

using Genome = char;    // Order of cities
using Fitness = double; // Total distance

unsigned int microsecond = 1000000;

int main()
{
int dnaLength = 0;
int glb_score = 0;

auto config = read_configuration("config.txt");

int populationSize = std::stoi(config["populationSize"]);
double mutationRate = std::stod(config["mutationRate"]);
std::string target = config["target"];
//std::string target = "To be or not to be that's not the question";
dnaLength = target.size();

  
  
  
  
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

  
  
  GeneticAlgorithm<Genome, Fitness> ga(populationSize, dnaLength,mutationRate);
  ga.SetFitFunc(fitnessFunction);
  int count = 0;
  
  
  
  while(glb_score != dnaLength)
  {
  usleep(0.01 * microsecond);//sleeps for 3 second
    system("clear");
    
    ga.RunGeneration();
    cout << "POP NO: " << count++ << " " << endl;
    
  }
  return 0;
}
