#include <iostream>
#include <GA.h>
#include <unordered_set>
using Genome = int;     // Order of cities
using Fitness = double; // Total distance
int numCities = 5;
// Distance matrix for a 5-city TSP
// Rows and columns represent cities (0 to 4)
// The value at [i][j] represents the distance from city i to city j

const double distanceMatrix[5][5] = {
    {0, 2, 9, 10, 7},
    {2, 0, 6, 4, 8},
    {9, 6, 0, 3, 7},
    {10, 4, 3, 0, 8},
    {7, 8, 7, 8, 0}};

std::function<std::vector<Genome>()> TSPInitializationFunction = []() -> std::vector<Genome>
{
  // Create an initial sequence from 0 to numCities-1
  std::vector<Genome> genome(numCities);
  std::iota(genome.begin(), genome.end(), 0); // Fills the genome with 0, 1, ..., numCities-1
  // Shuffle the sequence to produce a random permutation
  std::shuffle(genome.begin(), genome.end(), std::mt19937{std::random_device{}()});
  return genome;
};

auto fitnessFunction = [](const std::vector<Genome> &genome) -> Fitness
{
    Fitness totalDistance = 0;
    
    // Check for visiting itself
    for (size_t i = 0; i < genome.size(); i++)
    {
        if (genome[i] == i) return 0.0;  // City at position i in the genome should not be city i
    }

    // Check for visiting a city more than once
    std::unordered_set<Genome> visitedCities;
    for (const auto& city : genome)
    {
        if (visitedCities.count(city)) return 0.0;  // City is visited more than once
        visitedCities.insert(city);
    }

    // Compute total distance
    for (size_t i = 0; i < genome.size() - 1; i++)
    {
        totalDistance += distanceMatrix[genome[i]][genome[i+1]];
    }
    totalDistance += distanceMatrix[genome.back()][genome.front()];  // Return to the starting city

    // In TSP, we aim to minimize the distance, so a good score should be inversely related to the distance
    return 1.0 / (1.0 + totalDistance);  // Added 1 to avoid division by zero
};



int main()
{


  GeneticAlgorithm<Genome, Fitness> ga(300, numCities);
  ga.SetFitFunc(fitnessFunction);
ga.SetInitializationFunction(TSPInitializationFunction);
ga.InitializePopulation();
  for (size_t i = 0; i < 100; i++)
  {
    ga.RunGeneration();
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << i << "================================" << endl;
  }

  // std::cout << "Hello GA" << std::endl;
  return 0;
}