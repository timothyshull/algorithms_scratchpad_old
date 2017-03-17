#include <iostream>
#include "union_find.h"

int main() {
    int N;
    std::cin >> N;
    pc_uf uf{N};
    while (std::cin.good()) {
        int p;
        std::cin >> p;
        int q;
        std::cin >> q;
        if (uf.connected(p, q)) continue;
        uf.create_union(p, q);
        std::cout << p << " " << q;
    }
    std::cout << uf.get_count() << " components";
}
