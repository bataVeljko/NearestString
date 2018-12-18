#ifndef CLOSESTSTRING_HPP
#define CLOSESTSTRING_HPP

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <numeric>

struct Chromosome{
    std::string value;
    int fit;
};

class ClosestString {

public:
    ClosestString(const std::vector<std::string> &setOfStrings, const std::vector<char> &allowedGeneValues);
    void optimize();
    std::vector<Chromosome> initialPopulation();
    std::vector<Chromosome> selection(const std::vector<Chromosome> &population);
    std::vector<Chromosome> createGeneration(const std::vector<Chromosome> &forReproduction);

    std::pair<Chromosome, Chromosome> crossover(const Chromosome &parent1, const Chromosome &parent2);
    Chromosome mutation(Chromosome chromo);
    Chromosome pickOneTournament(const std::vector<Chromosome> & pop);

    int fitness(const std::string & current);

private:

    std::vector<std::string> _setOfStrings;
    std::vector<char> _allowedGeneValues;
    size_t _length;
    int _numOfIterations;
    unsigned _generationSize;
    double _mutationRate;
    unsigned _reproductionSize;
    int _k;
    Chromosome _best;

};

#endif // CLOSESTSTRING_HPP
