Genetic Algorithm implemented in C++, the first example to be implemented and demonstrated is TSP(the salesman problem)
# Genetic Algorithms

SETUP

Step 1: Initialize: Create a population of N elements, each with randomly generated DNA.

DRAW

Step 2: Selection: Evaluate the fitness of each element of the population and build a mating pool.

Step 3: Reproduction: Repeat N times:

1. Pick two parents with probability according to relative fitness.
2. Crossover — create a "child" by combining the DNA of these two parents.
3. Mutation — mutate the child's DNA based on a given probability.
4. Add the new child to a new population.

Step 4. Replace the old population with the new population and return to

# GAs implementation functionalities

1. **Initialization**:
    - `InitializePopulation(size_t populationSize, size_t genomeSize)`: Generates an initial population of genomes.
2. **Selection**:
    - `SelectParents()`: Selects parents based on their fitness for the crossover operation. Different selection strategies can be employed, such as roulette wheel selection, tournament selection, etc.
3. **Crossover**:
    - `Crossover(const GenomeType& parent1, const GenomeType& parent2)`: Combines two parent genomes to produce one or two offspring. There are various crossover strategies like one-point, two-point, and uniform crossover.
4. **Mutation**:
    - `Mutate(GenomeType& genome)`: Introduces small changes in a genome. The mutation rate is usually a parameter that controls how often a genome is mutated.
5. **Fitness Evaluation**:
    - `EvaluateFitness(const GenomeType& genome)`: Computes the fitness of a given genome.
6. **Population Management**:
    - `NextGeneration()`: Creates the next generation of genomes, typically involving selection, crossover, mutation, and possibly elitism (preserving the best genomes without modification).
7. **Query Functions**:
    - `GetBestGenome()`: Retrieves the genome with the highest fitness from the current population.
    - `GetAverageFitness()`: Computes the average fitness of the current population.
8. **Termination Check**:
    - `HasConverged()`: Checks if the GA has converged, i.e., if the solution is not improving significantly over generations or some other stopping criterion is met.
    - `MaxGenerationsReached()`: Checks if the maximum number of generations (iterations) has been reached.
9. **Configuration**:
    - `SetMutationRate(float rate)`: Sets the mutation rate.
    - `SetCrossoverRate(float rate)`: Sets the crossover rate.
    - `SetSelectionMethod(SelectionMethod method)`: Allows users to choose between various selection methods.
10. **Utilities**:
    - `GenerateRandomGenome()`: Generates a random genome.
    - `DisplayPopulation()`: Prints or returns a string representation of the current population for debugging or visualization purposes.
11. **Callbacks or Hooks**:
    - `OnGenerationBegin()`: A callback that gets triggered at the beginning of processing each generation.
    - `OnGenerationEnd()`: A callback that gets triggered at the end of processing each generation.
12. **Serialization and Logging**:
    - `SavePopulationToFile(const std::string& filePath)`: Saves the current population to a file.
    - `LoadPopulationFromFile(const std::string& filePath)`: Loads a population from a file.
    - `LogGenerationStats()`: Logs statistics for the current generation, like average fitness, best genome, etc.

When designing this API for a real-world application, it's crucial to ensure flexibility. Users might want to plug in their fitness functions, define custom mutation or crossover methods, or even use alternative selection techniques.
