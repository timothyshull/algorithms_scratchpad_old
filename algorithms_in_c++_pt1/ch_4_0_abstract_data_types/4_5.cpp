#include <iostream>
#include <cstdlib>
#include "list.h"

int main(int argc, char *argv[]) {
    int i, N = std::atoi(argv[1]), M = std::atoi(argv[2]);
    list l{N};
    int result = l.runJosephus(M);
    std::cout << result << "\n";

    return 0;
}