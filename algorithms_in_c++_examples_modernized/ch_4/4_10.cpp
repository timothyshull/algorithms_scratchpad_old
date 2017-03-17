#include <iostream>
#include <cstdlib>
#include "Union_find.h"

using std::cin;
using std::cout;

int main(int argc, char* argv[])
{
    int p;
    int q;
    int n = atoi(argv[1]);
    Union_find info(n);
    while (std::cin >> p >> q) {
        if (!info.find(p, q)) {
            info.unite(p, q);
            std::cout << " " << p << " " << q << "\n";
        }
    }
    return 0;
}

