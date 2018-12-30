#ifndef CLOSESTSTRING_HPP
#define CLOSESTSTRING_HPP

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <numeric>
#include <iterator>
#include <fstream>

struct Chromosome{
    std::string value;
    int fit;
};

class ClosestString {

public:
    ClosestString(const std::vector<std::string> &setOfStrings, const std::vector<char> &allowedGeneValues);

    ClosestString(const std::vector<std::string> &setOfStrings, const std::vector<char> &allowedGeneValues,
                  unsigned numOfIterations, unsigned generationSize, double mutationRate,
                  unsigned tournamentK, double crossoverProb);

    void optimize();
    std::vector<Chromosome> initialPopulation();
    std::vector<Chromosome> selection(const std::vector<Chromosome> &population);
    std::vector<Chromosome> createGeneration(const std::vector<Chromosome> &forReproduction);

    std::pair<Chromosome, Chromosome> crossover(const Chromosome &parent1, const Chromosome &parent2);
    void mutation(Chromosome &chromo);
    Chromosome pickOneTournament(const std::vector<Chromosome> & pop);

    int fitness(const std::string & current);
    bool stopConditions(size_t i, const std::vector<Chromosome> &chromosomes);

private:

    std::vector<std::string> _setOfStrings;
    std::vector<char> _allowedGeneValues;
    size_t _length;
    unsigned _numOfIterations;
    unsigned _generationSize;
    double _mutationRate;
    unsigned _reproductionSize;
    unsigned _tournamentK;
    double _crossoverProb;
    Chromosome _best;

    // best fitness from the last N iterations
    std::vector<int> _lastN;
    int _N;
};

#endif // CLOSESTSTRING_HPP
