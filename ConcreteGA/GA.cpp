#include <GA.h>

template <typename GenomeType, typename FitnessType>

GeneticAlgorithm<GenomeType, FitnessType>::GeneticAlgorithm

    (int popSize, int genomelength)

    : populationSize(popSize), GenomeLength(genomelength)
{
    for (int i = 0; i < popSize; ++i)
    {
        population.push_back(randomGenome());
        next_population.push_back(randomGenome());
    }
    population_score.reserve(populationSize);
    //next_population.reserve(populationSize);
}

template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::PrintGenome(vector<GenomeType> genome)
{
    for (size_t l = 0; l < GenomeLength; l++)
        {
          cout<<genome[l];
        }
        cout<<endl;
}


template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::RunGeneration()
{
    int scr = 0;
    child_count = 0;
    evaluate();
    select();
    // crossover();
     population = next_population;
    mutate();
    for (size_t i = 0; i < populationSize; i++)
    {
            
        scr=evaluateFitness(population[i]);
        //cout<<scr<<endl;
    }
    //  cout<<scr<<endl;
}

template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::evaluate()
{
   // Clear the population_score vector
    population_score.clear();

    FitnessType score = 0;
    for (int i = 0; i < populationSize; ++i)
    {
        score = evaluateFitness(population[i]);
        population_score.push_back(std::make_pair(i, score));
    }

    SortPopulationMap(population_score);
    PrintGenome(population[population_score[0].first]);
}

template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::select()
{
    // we will select the first 50% of the population
    int elite = populationSize / 2;
    if (elite % 2 == 0)
    {
        // elite is divisible by 2
        // nth to do
    }
    else
    {
        elite++;
    }
    // create elite indexes vector
    int count = 0;
    std::vector<int> elite_indexes ;
    elite_indexes.reserve(elite);
      for ( auto it = population_score.begin(); it != population_score.end() && count < elite; ++it, ++count) {
        //std::cout << it->first << " -> " << it->second << std::endl;
        elite_indexes[count] =  it->first;
    }
    for (size_t i = 0; i < elite; i++)
    {
       //cout<<elite_indexes[i]<<endl;
    }
    
    

    for (size_t i = 0; i < elite/2; i++)
    {
        // cout<<elite_indexes[i]<<elite_indexes[elite - 1]<<endl;
        crossover(population[elite_indexes[i]],population[elite_indexes[elite -1- i]]);
    }
    
}

template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::crossover
(vector<GenomeType> parent1, vector<GenomeType> parent2)
{
    vector<GenomeType> child1;
    vector<GenomeType> child2;
    child1.resize(GenomeLength);
    child2.resize(GenomeLength);
    int mid_genome = GenomeLength/2;
   
    for (size_t i = 0; i < mid_genome; i++)
    {
        child1[i]= parent1[i];
        child1[GenomeLength-1-i] = parent2[GenomeLength-1-i];
        child2[i]= parent2[i];
        child2[GenomeLength-1-i] = parent1[GenomeLength-1-i];
    }
    //cout<<"finished mating"<<endl;
    next_population[child_count++] = parent1;
    next_population[child_count++] = parent2;
    next_population[child_count++] = child1;
    next_population[child_count++] = child2;



}

template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::mutate()
{
    // Set a non-zero mutation rate
    double staticMutationRate = 0.05; // for a 5% mutation rate

    // Use Mersenne Twister as the random number generator
    std::mt19937 rng(std::random_device{}());
    
    // Create a uniform distribution for choosing the genome mutation position
    std::uniform_int_distribution<int> position_dist(0, GenomeLength - 1);
    
    // Create a uniform distribution for the mutation itself (this range assumes ASCII values)
    std::uniform_int_distribution<int> mutation_dist(32, 126);

    // Create a uniform distribution for deciding if a genome should mutate
    std::uniform_real_distribution<double> mutation_chance(0.0, 1.0);

    for(auto& individual : population) {
        // Check if this genome should mutate
        if(mutation_chance(rng) < staticMutationRate) {
            // Choose a random position for mutation
            int randomValue = position_dist(rng);
            
            // Mutate the genome at the chosen position
            individual[randomValue] = static_cast<GenomeType>(mutation_dist(rng));
            
            // Optional print for debugging
           // cout << "Mutate" << endl;
        }
    }
}


// HELPER functions

// RANDOMGENOME
//  Create Random genome to fill the first population

template <typename GenomeType, typename FitnessType>
std::vector<GenomeType>
GeneticAlgorithm<GenomeType, FitnessType>::randomGenome()
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

// SetFitFunc
//  member function to set the fitness function by passing a defined lamda equation that will test the fit result of each single genome

template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::SetFitFunc(std::function<FitnessType(const std::vector<GenomeType> &)> fitnessFunc)
{
    evaluateFitness = fitnessFunc;
}

// SortPopulationMap
// to sort the passed score map of the population while keeping the indixes as the original population
template <typename GenomeType, typename FitnessType>
void GeneticAlgorithm<GenomeType, FitnessType>::SortPopulationMap(std::vector<std::pair<int, FitnessType>> score_map)
{
    std::sort(population_score.begin(), population_score.end(),
              [](const std::pair<int, int> &a, const std::pair<int, int> &b)
              {
                  return a.second > b.second;
              });

    for (const auto &p : population_score)
    {
        //std::cout << "Genome index: " << p.first << ", Score: " << p.second << std::endl;
    }
}

template class GeneticAlgorithm<char, double>;
template class GeneticAlgorithm<char, int>;