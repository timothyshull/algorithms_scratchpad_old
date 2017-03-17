#include <sstream>
#include <iostream>
#include "union_find.h"

static const int max_size = 1000;

pc_uf::pc_uf(int n) : count{n},
                      parent{vector<int>(static_cast<unsigned long>(n))},
                      rank{vector<int>(static_cast<unsigned long>(n))} {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int pc_uf::find(int p) {
    validate(p);
    while (p != parent[p]) {
        parent[p] = parent[parent[p]];
        p = parent[p];
    }
    return p;
}

bool pc_uf::connected(int p, int q) {
    return find(p) == find(q);
}

void pc_uf::create_union(int p, int q) {
    int root_p = find(p);
    int root_q = find(q);
    if (root_p == root_q)
        return;

    if (rank[root_p] < rank[root_q])
        parent[root_p] = root_q;
    else if (rank[root_p] > rank[root_q])
        parent[root_q] = root_p;
    else {
        parent[root_q] = root_p;
        rank[root_p]++;
    }
    count--;
}

void pc_uf::validate(int p) {
    unsigned long n = parent.size();
    if (p < 0 || p >= n) {
        std::ostringstream err_str;
        err_str << "index " << p << " is not between 0 and " << (n - 1);
        throw std::out_of_range(err_str.str());
    }
}

void path_compression_uf() {
    int i, j, p, q, id[max_size], sz[max_size];
    for (i = 0; i < max_size; i++) {
        id[i] = i;
        sz[i] = 1;
    }
    while (std::cin >> p >> q) {
        for (i = p; i != id[i]; i = id[i])
            id[i] = id[id[i]];
        for (j = q; j != id[j]; j = id[j])
            id[j] = id[id[j]];
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
