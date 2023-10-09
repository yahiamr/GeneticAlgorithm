#include <vector>
#include <algorithm>
#include <random>
#include <functional>
#include <iostream>
#include <string>
using namespace std;

template<typename GenomeType, typename FitnessType>
class GeneticAlgorithm {
    public:
        GeneticAlgorithm(int popSize, int genomelength);
        ~GeneticAlgorithm() = default;
        void SetGenomeLength(int length);
        void SetPopulationSize(int popsize);
        void RunGeneration();
        void SetFitFunc(std::function<FitnessType(const std::vector<GenomeType>&)> fitnessFunc);
    private:
        //methods
        void evaluate();
        void select();
        void crossover();
        void mutate();
        std::vector<GenomeType> randomGenome();
        // variables
        std::vector<GenomeType> population_score;
        int populationSize;
        int GenomeLength;
        std::vector<std::vector<GenomeType>> population;
        std::function<FitnessType(const std::vector<GenomeType>&)> evaluateFitness;

};