#include <GA.h>

template <typename GenomeType, typename FitnessType>

GeneticAlgorithm<GenomeType, FitnessType>::GeneticAlgorithm

    (int popSize, int genomelength)

    : populationSize(popSize), GenomeLength(genomelength)
{
    for (int i = 0; i < popSize; ++i)
    {
        population.push_back(randomGenome());
    }
    population_score.reserve(populationSize);
}

template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::RunGeneration
()
{
    evaluate();
    select();
    crossover();
    mutate();
}

template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::SetFitFunc
(std::function<FitnessType(const std::vector<GenomeType> &)> fitnessFunc)
{
    evaluateFitness = fitnessFunc;
}

template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::evaluate
()
{
    for (int i = 0; i < populationSize; ++i)
    {
       population_score[i] =evaluateFitness(population[i]);
    }
}

template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::select
()
{
}

template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::crossover
()
{
}

template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::mutate
()
{
}

template <typename GenomeType, typename FitnessType>
std::vector<GenomeType>
GeneticAlgorithm<GenomeType, FitnessType>::randomGenome
()
{
    std::vector<GenomeType> gnome(GenomeLength);
    // Create a Mersenne Twister random number generator
    std::mt19937 rng(std::random_device{}());

    // Create a uniform distribution
    std::uniform_int_distribution<int> dist(32, 126);

    for (size_t i = 0; i < gnome.size(); i++)
    {
        gnome[i] = static_cast<GenomeType>(dist(rng));
        //    cout<<(static_cast<GenomeType>) rand()<<endl;
    }
    return gnome;
}

template class GeneticAlgorithm<char, double>;