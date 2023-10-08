#include <GA.h>



template<typename GenomeType, typename FitnessType>

GeneticAlgorithm<GenomeType, FitnessType>::GeneticAlgorithm

(int popSize, int genomelength)

:populationSize(popSize), GenomeLength(genomelength)
{
    for (int i = 0; i < popSize; ++i) {
            population.push_back(randomGenome());
        
            for (auto elem : population[i]) {
          //  cout << elem;
    }
 
   // cout << endl;
    }
        
}

template<typename GenomeType, typename FitnessType>
void
GeneticAlgorithm<GenomeType, FitnessType>::RunGeneration
()
{
    for (size_t l = 0; l < population.size(); l++)
    {
  
        evaluateFitness(population[l]);
        //cout<<population[l][i];
   
    }
    //evaluateFitness();
    evaluate();
    select();
    crossover();
    mutate();
}

template<typename GenomeType, typename FitnessType>
void 
GeneticAlgorithm<GenomeType, FitnessType>::SetFitFunc(std::function<FitnessType(const std::vector<GenomeType>&)> fitnessFunc) {
    evaluateFitness = fitnessFunc;
}


template<typename GenomeType, typename FitnessType>
void
GeneticAlgorithm<GenomeType, FitnessType>::evaluate
()
{
for (auto& genome :population)
{
evaluateFitness(genome);
}

}

template<typename GenomeType, typename FitnessType>
void
GeneticAlgorithm<GenomeType, FitnessType>::select
()
{

}

template<typename GenomeType, typename FitnessType>
void
GeneticAlgorithm<GenomeType, FitnessType>::crossover
()
{

}

template<typename GenomeType, typename FitnessType>
void
GeneticAlgorithm<GenomeType, FitnessType>::mutate
()
{

}

template<typename GenomeType, typename FitnessType>
std::vector<GenomeType>
GeneticAlgorithm<GenomeType, FitnessType>::randomGenome(){
std::vector<GenomeType> gnome(GenomeLength);
            for (size_t i = 0; i < gnome.size(); i++)
            {
               gnome[i] = static_cast<GenomeType>(32 + ( std::rand() % ( 126 - 32 + 1 ) ));
            //    cout<<(static_cast<GenomeType>) rand()<<endl;
            }
return gnome;            

}

template class GeneticAlgorithm<char, double>;