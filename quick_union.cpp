#include <sstream>
#include <iostream>
#include "quick_union.h"

static const int max_size = 1000;

weighted_quick_union::weighted_quick_union(int n) : count{n},
                                  parent{vector<int>(static_cast<unsigned long>(n))} {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
}

int weighted_quick_union::find(int p) {
    validate(p);
    while (p != parent[p])
        p = parent[p];
    return p;
}

inline int weighted_quick_union::get_count() { return count; }

bool weighted_quick_union::connected(int p, int q) {
    return find(p) == find(q);
}

void weighted_quick_union::create_union(int p, int q) {
    int root_p = find(p);
    int root_q = find(q);
    if (root_p == root_q) return;
    parent[root_p] = root_q;
    count--;
}

void weighted_quick_union::validate(int p) {
    unsigned long n = parent.size();
    if (p < 0 || p >= n) {
        std::ostringstream err_str;
        err_str << "index " << p << " is not between 0 and " << (n - 1);
        throw std::out_of_range(err_str.str());
    }
}

void simple_weighted_quick_union() {
    int i, j, p, q, id[max_size];
    while (std::cin >> p >> q) {
        for (i = p; i != id[i]; i = id[i]);
        for (j = q; j != id[j]; j = id[j]);
        if (i == j) continue;
        id[i] = j;
        std::cout << " " << p << " " << q << std::endl;
    }
}
