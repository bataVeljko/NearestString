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
#include <climits>

struct Chromosome{
    std::string value;
    int fit;
};

class ClosestString {

public:
    //First, temporary constructor, without parameters
    ClosestString(const std::vector<std::string> &setOfStrings, const std::vector<char> &allowedGeneValues);

    //Main constructor, with all parameters for genetic algorithm
    ClosestString(const std::vector<std::string> &setOfStrings, const std::vector<char> &allowedGeneValues,
                  unsigned numOfIterations, unsigned generationSize, double mutationRate,
                  unsigned tournamentK, double crossoverProb);

    //Main function, all begin here
    void optimize();
    //Create random population, from allowed gene values
    std::vector<Chromosome> initialPopulation();
    //tournament selection, with parametar K, which goes from GenerationSize/5 to GenerationSize
    std::vector<Chromosome> selection(const std::vector<Chromosome> &population);
    //Use selected chromosomes, do uniform crossover on 2 parents to get 2 children, some of children are than mutated and add to vector
    std::vector<Chromosome> createGeneration(const std::vector<Chromosome> &forReproduction);
    //Uniform crossover
    std::pair<Chromosome, Chromosome> crossover(const Chromosome &parent1, const Chromosome &parent2);
    //Mutation on random bit of chromosome value, with probability MutationRate
    void mutation(Chromosome &chromo);
    //From all chromosomes that are forwarded as parameter, pick and return the one with best fitness
    Chromosome pickOneTournament(const std::vector<Chromosome> & pop);
    //Calculate fitness for the forwarded string
    int fitness(const std::string & current);
    //Stop conditions for whole program
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
