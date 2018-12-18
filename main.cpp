#include <iostream>
#include "closeststring.hpp"

int main() {

    ClosestString cs({"AG"}, {'C', 'A', 'G', 'T'});
    cs.optimize();

    return 0;
}
