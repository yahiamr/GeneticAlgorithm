/**
 * @file GA.h
 * @brief Contains the GeneticAlgorithm class which implements a genetic algorithm
 */

#include <vector>
#include <algorithm>
#include <random>
#include <functional>
#include <iostream>
#include <string>
using namespace std;

/**
 * @class GeneticAlgorithm
 * @tparam GenomeType The data type of the genome
 * @tparam FitnessType The data type of the fitness score
 * @brief Implements a simple genetic algorithm
 */
template <typename GenomeType, typename FitnessType>
class GeneticAlgorithm
{
public:
    /** 
     * @brief Constructor for the GeneticAlgorithm class
     * @param popSize Population size
     * @param genomelength Length of each genome
     */
    GeneticAlgorithm(int popSize, int genomelength, double mutationrate);
    
    /**
     * @brief Destructor for the GeneticAlgorithm class
     */
    ~GeneticAlgorithm() = default;

    /**
     * @brief Sets the length of the genome
     * @param length New length for the genome
     */
    void SetGenomeLength(int length);

    /**
     * @brief Sets the size of the population
     * @param popsize New population size
     */
    void SetPopulationSize(int popsize);

    /**
     * @brief Runs a single generation of the genetic algorithm
     */
    void RunGeneration();

    /**
     * @brief Assigns the fitness function to be used in the genetic algorithm
     * @param fitnessFunc Lambda or function returning the fitness score of a genome
     */
    void SetFitFunc(std::function<FitnessType(const std::vector<GenomeType> &)> fitnessFunc);

    /**
     * @brief Prints the genome to the console
     * @param genome The genome to be printed
     */
    void PrintGenome(vector<GenomeType>);

private:
    /**
     * @brief Evaluates the fitness of each genome in the population
     */
    void evaluate();

    /**
     * @brief Selects genomes from the population based on their fitness
     */
    void select();

    /**
     * @brief Performs crossover between two parent genomes to produce offspring
     * @param parent1 The first parent genome
     * @param parent2 The second parent genome
     */
    void crossover(vector<GenomeType> parent1, vector<GenomeType> parent2);

    /**
     * @brief Mutates genomes in the population
     */
    void mutate();

    /**
     * @brief Generates a random genome
     * @return A random genome
     */
    std::vector<GenomeType> randomGenome();

    /**
     * @brief Sorts the population based on their fitness scores
     * @param score_map A map of genome indices and their fitness scores
     */
    void SortPopulationMap(std::vector<std::pair<int, FitnessType>> score_map);

    std::vector<std::pair<int, FitnessType>> population_score; ///< List of pairs of genome indices and their fitness scores
    int populationSize; ///< Size of the population
    int GenomeLength; ///< Length of each genome
    double MutationRate; ///< Mutation rate
    std::vector<std::vector<GenomeType>> population; ///< Current population of genomes
    std::vector<std::vector<GenomeType>> next_population; ///< Next generation of genomes
    int child_count = 0; ///< Counter for the number of children produced in the current generation
    std::function<FitnessType(const std::vector<GenomeType> &)> evaluateFitness; ///< Fitness evaluation function
};

