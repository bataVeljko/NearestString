#include "closeststring.hpp"

int main(int argc, char **argv) {

    //arguments: program, NumOfIteration, GenerationSize, MutatioRate, TournamentK, CrossoverProbability
    if (argc != 6) {
        std::cerr << "number of arguments must be 6" << std::endl;
        exit(1);
    }

//    std::ifstream in("words", std::ifstream::in);
//    std::string tmp;
//    while (in) {
//        std::getline(in, tmp);
//        setOfStrings.push_back(tmp);
//    }

    //Set of string, for now, will be loading from txt file
    std::vector<std::string> setOfStrings {"AGT", "ATT", "GAT", "CCC", "CCT"};

    ClosestString t(setOfStrings, {'A', 'C', 'T', 'G'}, unsigned(atoi(argv[1])), unsigned(atoi(argv[2])),
            atof(argv[3]), unsigned(atoi(argv[4])), atof(argv[5]));
    t.optimize();

    return 0;
}
