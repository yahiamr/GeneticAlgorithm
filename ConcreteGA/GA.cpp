#include <GA.h>

// Constructor: Initializes the population and the next generation with random genomes
template <typename GenomeType, typename FitnessType>
GeneticAlgorithm<GenomeType, FitnessType>::GeneticAlgorithm(int popSize, int genomelength)
    : populationSize(popSize), GenomeLength(genomelength)
{
    // Initialize the population and next population with random genomes
    for (int i = 0; i < popSize; ++i)
    {
        population.push_back(randomGenome());
        next_population.push_back(randomGenome());
    }
    population_score.reserve(populationSize);  // Reserve space for the population score
}

// Print the genome content
template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::PrintGenome(vector<GenomeType> genome)
{
    for (size_t l = 0; l < GenomeLength; l++)
    {
        cout << genome[l];
    }
    cout << endl;
}

// Run one generation of the genetic algorithm
template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::RunGeneration()
{
    int scr = 0;
    child_count = 0;  // Reset child count
    evaluate();       // Evaluate the population fitness
    select();         // Select genomes for reproduction
    population = next_population;  // Set the current population as the next one
    mutate();         // Apply mutations

    // Compute fitness for each individual in the population
    for (size_t i = 0; i < populationSize; i++)
    {
        scr = evaluateFitness(population[i]);
    }
}

// Evaluate the fitness of the entire population
template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::evaluate()
{
    population_score.clear();  // Clear the population_score vector
    FitnessType score = 0;
    // Evaluate fitness for each genome and store it with its index
    for (int i = 0; i < populationSize; ++i)
    {
        score = evaluateFitness(population[i]);
        population_score.push_back(std::make_pair(i, score));
    }

    SortPopulationMap(population_score);    // Sort population based on fitness
    PrintGenome(population[population_score[0].first]);  // Print the best genome
}

// Select genomes for reproduction
template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::select()
{
    int elite = populationSize / 2;  // Select the top 50% genomes
    if (elite % 2 != 0) elite++;     // Ensure elite count is even

    // Collect indices of elite genomes
    int count = 0;
    std::vector<int> elite_indexes ;
    elite_indexes.reserve(elite);
    for ( auto it = population_score.begin(); it != population_score.end() && count < elite; ++it, ++count) {
        elite_indexes[count] = it->first;
    }

    // Crossover elite genomes to produce children
    for (size_t i = 0; i < elite / 2; i++)
    {
        crossover(population[elite_indexes[i]], population[elite_indexes[elite - 1 - i]]);
    }
}

// Crossover two parent genomes to produce two children
template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::crossover(vector<GenomeType> parent1, vector<GenomeType> parent2)
{
    vector<GenomeType> child1(GenomeLength);
    vector<GenomeType> child2(GenomeLength);
    int mid_genome = GenomeLength / 2;

    // Create children by combining parts of parents
    for (size_t i = 0; i < mid_genome; i++)
    {
        child1[i] = parent1[i];
        child1[GenomeLength - 1 - i] = parent2[GenomeLength - 1 - i];
        child2[i] = parent2[i];
        child2[GenomeLength - 1 - i] = parent1[GenomeLength - 1 - i];
    }

    // Add parents and children to the next population
    next_population[child_count++] = parent1;
    next_population[child_count++] = parent2;
    next_population[child_count++] = child1;
    next_population[child_count++] = child2;
}

// Mutate genomes in the population
template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::mutate()
{
    double staticMutationRate = 0.07;  // 5% mutation rate

    // Random number generators
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> position_dist(0, GenomeLength - 1);
    std::uniform_int_distribution<int> mutation_dist(32, 126);
    std::uniform_real_distribution<double> mutation_chance(0.0, 1.0);

    // Apply mutation based on mutation rate
    for(auto& individual : population)
    {
        if(mutation_chance(rng) < staticMutationRate)
        {
            int randomValue = position_dist(rng);
            individual[randomValue] = static_cast<GenomeType>(mutation_dist(rng));
        }
    }
}

// Generate a random genome
template <typename GenomeType, typename FitnessType>
std::vector<GenomeType> GeneticAlgorithm<GenomeType, FitnessType>::randomGenome()
{
    std::vector<GenomeType> gnome(GenomeLength);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(32, 126);

    // Fill genome with random values
    for (size_t i = 0; i < gnome.size(); i++)
    {
        gnome[i] = static_cast<GenomeType>(dist(rng));
    }
    return gnome;
}

// Set the fitness function
template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::SetFitFunc(std::function<FitnessType(const std::vector<GenomeType> &)> fitnessFunc)
{
    evaluateFitness = fitnessFunc;
}

// Sort the population based on their fitness
template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::SortPopulationMap(std::vector<std::pair<int, FitnessType>> score_map)
{
    std::sort(population_score.begin(), population_score.end(),
              [](const std::pair<int, int> &a, const std::pair<int, int> &b)
              {
                  return a.second > b.second;
              });
}

// Explicit template instantiations
template class GeneticAlgorithm<char, double>;
template class GeneticAlgorithm<char, int>;
