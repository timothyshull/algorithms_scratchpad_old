#include <iostream>
#include "weighted_quick_union.h"

int main() {
    int N;
    std::cin >> N;
    weighted_quick_union uf{N};
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
