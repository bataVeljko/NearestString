#include "closeststring.hpp"

int main(int argc, char **argv) {

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

    std::vector<std::string> setOfStrings {"AGT", "ATT", "GAT", "CCC", "CCT"};

    ClosestString t(setOfStrings, {'A', 'C', 'T', 'G'}, unsigned(atoi(argv[1])), unsigned(atoi(argv[2])),
            atof(argv[3]), unsigned(atoi(argv[4])), atof(argv[5]));
    t.optimize();

//    ClosestString cs({"AGT", "ATT", "GAT", "CCC"}, {'A', 'C', 'T', 'G'});
//    cs.optimize();

    return 0;
}
