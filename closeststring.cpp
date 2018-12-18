#include "closeststring.hpp"

ClosestString::ClosestString(const std::vector<std::string> &setOfStrings, const std::vector<char> &allowedGeneValues) :
    _setOfStrings(setOfStrings), _allowedGeneValues(allowedGeneValues)
{
    _length = _setOfStrings[0].length();
    _numOfIterations = 100;
    _generationSize = 20;
    _mutationRate = 0.01;
    _reproductionSize = 20;
    _k = 5;
}

std::vector<Chromosome> ClosestString::initialPopulation(){

    srand(time(nullptr));

    std::vector<Chromosome> initPopulation;
    for (unsigned i = 0; i < _generationSize; ++i){
        std::vector<char> geneticCode;
        for (size_t j = 0; j < _length; j++){
            size_t pos = rand() % _allowedGeneValues.size();
            geneticCode.push_back(_allowedGeneValues[pos]);
        }
        std::string current = std::string(std::cbegin(geneticCode), std::cend(geneticCode));
        initPopulation.push_back(Chromosome{current, fitness(current)});
    }
    return initPopulation;
}

std::vector<Chromosome> ClosestString::selection(const std::vector<Chromosome> &population) {
    std::vector<Chromosome> forReproduction;
    for(size_t i = 0, n = population.size(); i < n; ++i){
        forReproduction.push_back(pickOneTournament(population));
    }

    for(size_t i = 0, n = forReproduction.size(); i < n; ++i){
        std::cout << forReproduction[i].fit << " " << forReproduction[i].value << std::endl;
    }

    return forReproduction;
}

Chromosome ClosestString::pickOneTournament(const std::vector<Chromosome> &pop) {
    //set here inf
    Chromosome bestC{"", 1000};
    for(int i = 0; i < _k; ++i){
        size_t pos = rand() % pop.size();
        if(pop[pos].fit < bestC.fit){
            bestC = pop[pos];
        }
    }
    return bestC;
}

std::vector<Chromosome> ClosestString::createGeneration(const std::vector<Chromosome> &forReproduction) {
    //crossover
    //mutation
    return {Chromosome{"A", 0}};
}

std::pair<Chromosome, Chromosome> ClosestString::crossover(const Chromosome &parent1, const Chromosome &parent2)
{
    return {{"", 0}, {"", 0}};
}

Chromosome ClosestString::mutation(Chromosome chromo)
{
    return {"", 0};
}

int hamingDistance(const std::string & s1, const std::string & s2){
    if (s1.length() != s2.length())
        return -1;

    return std::inner_product(std::cbegin(s1), std::cend(s1), std::cbegin(s2), 0,
                              [] (int left, int right) {return left + right;},
                              [] (char c1, char c2) {return c1 != c2 ? 1 : 0;});
}

int ClosestString::fitness(const std::string &current)
{
    auto i = std::max_element(std::cbegin(_setOfStrings), std::cend(_setOfStrings),
                            [current](std::string s1, std::string s2){return hamingDistance(s1, current) < hamingDistance(s2, current);});

    return hamingDistance(*i, current);
}

bool compare(Chromosome c1, Chromosome c2){
    return c1.fit < c2.fit;
}

void ClosestString::optimize(){
    std::vector<Chromosome> chromosomes = initialPopulation();

    std::cout << "-------------------------" << std::endl;
    for (const auto & c : chromosomes) {
        std::cout << c.value << " " << c.fit << std::endl;
    }

    int i = 0;
    while(i < _numOfIterations){
        std::vector<Chromosome> forReproduction = selection(chromosomes);
        chromosomes = createGeneration(forReproduction);
        _best = *(std::max_element(std::cbegin(chromosomes), std::cend(chromosomes), compare));
        //std::cout << "Iteration: " << i << " -> " << _best.value << " " << _best.fit << std::endl;
        i++;
    }
    std::cout << "end" << std::endl;
}
