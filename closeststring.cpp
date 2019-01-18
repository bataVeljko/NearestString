#include "closeststring.hpp"

ClosestString::ClosestString(const std::vector<std::string> &setOfStrings, const std::vector<char> &allowedGeneValues) :
    _setOfStrings(std::move(setOfStrings)), _allowedGeneValues(std::move(allowedGeneValues))
{
    _length = _setOfStrings[0].length();
    _numOfIterations = 100;
    _generationSize = 20;
    _mutationRate = 0.01;
    _reproductionSize = 20;
    _tournamentK = 5;
    _crossoverProb = 0.5;
    // _N = _numOfIterations / 4;
}

ClosestString::ClosestString(const std::vector<std::string> &setOfStrings, const std::vector<char> &allowedGeneValues,
                             unsigned numOfIterations, unsigned generationSize, double mutationRate,
                             unsigned tournamentK, double crossoverProb)
    : _setOfStrings(std::move(setOfStrings)),
      _allowedGeneValues(std::move(allowedGeneValues)),
      _numOfIterations(numOfIterations),
      _generationSize(generationSize),
      _mutationRate(mutationRate),
      _reproductionSize(generationSize),
      _tournamentK(tournamentK),
      _crossoverProb(crossoverProb)
{
    _length = _setOfStrings[0].length();
    // _N = _numOfIterations / 4;

    _best = Chromosome{"", int(_length + 1)};

    printf("%18d %14d %12.2lf %14d %20.1lf ", _numOfIterations, _generationSize, _mutationRate, _tournamentK, _crossoverProb);
}

std::vector<Chromosome> ClosestString::initialPopulation(){

    srand(unsigned(time(nullptr)));

    std::vector<Chromosome> initPopulation;
    for (unsigned i = 0; i < _generationSize; ++i){
        std::vector<char> geneticCode;
        //make one string as vector<char> from allowed charachers
        for (size_t j = 0; j < _length; j++){
            size_t pos = unsigned(rand()) % _allowedGeneValues.size();
            geneticCode.push_back(_allowedGeneValues[pos]);
        }
        //make string from vector<char>
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

    return forReproduction;
}

Chromosome ClosestString::pickOneTournament(const std::vector<Chromosome> &pop) {
    Chromosome bestC{"", INT_MAX};
    for(size_t i = 0; i < _tournamentK; ++i){
        size_t pos = unsigned(rand()) % pop.size();
        if(pop[pos].fit < bestC.fit){
            bestC = pop[pos];
        }
    }
    return bestC;
}

std::vector<Chromosome> ClosestString::createGeneration(const std::vector<Chromosome> &forReproduction) {

    std::vector<Chromosome> newGeneration;
    for (size_t i = 0; i < _generationSize; i+=2) {
        size_t index1 = unsigned(rand()) % forReproduction.size();
        size_t index2 = unsigned(rand()) % forReproduction.size();

        std::pair<Chromosome, Chromosome> children =
                crossover(forReproduction[index1], forReproduction[index2]);

        mutation(children.first);
        mutation(children.second);

        newGeneration.push_back(children.first);
        newGeneration.push_back(children.second);
    }

    return newGeneration;
}

std::pair<Chromosome, Chromosome> ClosestString::crossover(const Chromosome &parent1, const Chromosome &parent2) {

    size_t n = parent1.value.size();
    std::string child1, child2;

    child1.resize(n);
    child2.resize(n);

    for (size_t i = 0; i < n; ++i) {
        double tmp = double((double(rand()) / RAND_MAX));
        if (tmp < _crossoverProb) {
            child1.at(i) = parent1.value.at(i);
            child2.at(i) = parent2.value.at(i);
        } else {
            child2.at(i) = parent1.value.at(i);
            child1.at(i) = parent2.value.at(i);
        }
    }

    return {Chromosome{child1, fitness(child1)}, Chromosome{child2, fitness(child2)}};
}

void ClosestString::mutation(Chromosome &chromo) {

    double mutationImpossible = (double(rand()) / RAND_MAX);
    if (mutationImpossible < _mutationRate) {
        //select position in string that will be changed
        size_t index = unsigned(rand()) % chromo.value.size();
        //select which charachter will be set on selected position in chromosome value
        size_t pos = unsigned(rand()) % _allowedGeneValues.size();

        chromo.value.at(index) = _allowedGeneValues.at(pos);
        chromo.fit = fitness(chromo.value);
    }
}

int hamingDistance(const std::string & s1, const std::string & s2){
    if (s1.length() != s2.length())
        return -1;

    return std::inner_product(std::cbegin(s1), std::cend(s1), std::cbegin(s2), 0,
                              [] (int left, int right) {return left + right;},
                              [] (char c1, char c2) {return c1 != c2 ? 1 : 0;});
}

int ClosestString::fitness(const std::string &current) {
    //Getting position in setOfStrings vector, that belongs to string which is furthest from Current chromosome value from population
    auto i = std::max_element(std::cbegin(_setOfStrings), std::cend(_setOfStrings),
                            [current](std::string s1, std::string s2){return hamingDistance(s1, current) < hamingDistance(s2, current);});

    //Calculate their distance
    return hamingDistance(*i, current);
}

bool compare(Chromosome c1, Chromosome c2){
    return c1.fit < c2.fit;
}

void ClosestString::optimize(){
    std::vector<Chromosome> chromosomes = initialPopulation();

    size_t currIteration = 0;
    while(stopConditions(currIteration, chromosomes)){
        std::vector<Chromosome> forReproduction = selection(chromosomes);
        chromosomes = createGeneration(forReproduction);

        //Chromosome with smallest fit in population
        _best = *(std::min_element(std::cbegin(chromosomes), std::cend(chromosomes), compare));
        currIteration++;
    }
    // printf("%13zu ", currIteration);
    // size_t numOfSpaces = 9 - _best.value.size();
    // std::string spaces(numOfSpaces, ' ');
    // std::cout << spaces << _best.value;
    printf(" %7d", _best.fit);
}

bool ClosestString::stopConditions(size_t currIteration, const std::vector<Chromosome> &) {
    if (currIteration >= _numOfIterations)
        return false;

    if (_best.fit == 0)
        return false;

    // We won't use 0th generation, because it's inital population and best chromosome hasn't been initializated yet
    // if (currIteration) {
    //     if (int(_lastN.size()) < _N) {
    //         _lastN.push_back(_best.fit);
    //     } else {
    //         // if we have the same result in the last N generations, we stop
    //         int sum = std::accumulate(std::cbegin(_lastN), std::cend(_lastN), 0);
    //         if (sum / _N == _lastN[0]) {
    //             return false;
    //         }
    //         // else we add a new one, first we place first element on the back
    //         // and then we replace it
    //         std::rotate(std::begin(_lastN), std::end(_lastN)-1, std::end(_lastN));
    //         _lastN.back() = _best.fit;
    //     }
    // }

    return true;
}





