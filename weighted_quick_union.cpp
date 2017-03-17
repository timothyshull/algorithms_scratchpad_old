#include <sstream>
#include <iostream>
#include "weighted_quick_union.h"

static const int max_size = 1000;

weighted_quick_union::weighted_quick_union(int n) : count{n},
                                                    parent{vector<int>(static_cast<unsigned long>(n))},
                                                    size{vector<int>(static_cast<unsigned long>(n))} {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        size[i] = 1;
    }
}

int weighted_quick_union::find(int p) {
    validate(p);
    while (p != parent[p])
        p = parent[p];
    return p;
}

bool weighted_quick_union::connected(int p, int q) {
    return find(p) == find(q);
}

void weighted_quick_union::create_union(int p, int q) {
    int root_p = find(p);
    int root_q = find(q);
    if (root_p == root_q) return;

    if (size[root_p] < size[root_q]) {
        parent[root_p] = root_q;
        size[root_q] += size[root_p];
    } else {
        parent[root_q] = root_p;
        size[root_p] += size[root_q];
    }
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

void weighted_uf() {
    int i, j, p, q, id[max_size], sz[max_size];
    for (i = 0; i < max_size; i++) {
        id[i] = i;
        sz[i] = 1;
    }
    while (std::cin >> p >> q) {
        for (i = p; i != id[i]; i = id[i]);
        for (j = q; j != id[j]; j = id[j]);
        if (i == j) continue;
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
        } else {
            id[j] = i;
            sz[i] += sz[j];
        }
        std::cout << " " << p << " " << q << std::endl;
    }
}
