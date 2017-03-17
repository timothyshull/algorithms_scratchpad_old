#include <sstream>
#include <iostream>
#include "union_find.h"

static const int max_size = 1000;

weighted_quick_union::weighted_quick_union(int n) : count{n},
                                parent{vector<int>(static_cast<unsigned long>(n))} {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
}

int weighted_quick_union::find(int p) {
    validate(p);
    return parent[p];
}

bool weighted_quick_union::connected(int p, int q) {
    validate(p);
    validate(q);
    return parent[p] == parent[q];
}

void weighted_quick_union::create_union(int p, int q) {
    validate(p);
    validate(q);
    int p_id = parent[p];
    int q_id = parent[q];

    if (p_id == q_id) return;

    for (int i = 0; i < parent.size(); i++)
        if (parent[i] == p_id) parent[i] = q_id;
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

void simple_union_find() {
    int i, p, q, id[max_size];
    while (std::cin >> p >> q) {
        int t = id[p];
        if (t == id[q]) continue;
        for (i = 0; i < max_size; i++)
            if (id[i] == t) id[i] = id[q];
        std::cout << " " << p << " " << q << std::endl;
    }
}
