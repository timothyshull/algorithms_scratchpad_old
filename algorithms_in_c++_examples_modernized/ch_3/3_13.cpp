#include <iostream>
#include "list.h"

int main(int argc, char* argv[])
{
    int n{std::stoi(argv[1])};
    int m{std::stoi(argv[2])};
    construct<int>(n);
    int i;
    Raw_node_pointer<int> x;
    Raw_node_pointer<int> t;
    for (i = 2, x = new_node(1); i <= n; ++i) {
        t = new_node(i);
        insert(x, t);
        x = t;
    }
    while (x != next(x)) {
        for (i = 1; i < m; ++i) { x = next(x); }
        delete_node(remove(x));
    }
    std::cout << item(x) << "\n";
    return 0;
}

