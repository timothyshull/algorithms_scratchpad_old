#ifndef ALGS_CPP_UNION_FIND_H
#define ALGS_CPP_UNION_FIND_H

#include <vector>
#include <bitset>

using std::vector;
using std::bitset;

class weighted_quick_union {
private:
    vector<int> parent;
    int count;
public:
    weighted_quick_union(int n);

    int find(int p);

    inline int get_count() { return count; }

    bool connected(int p, int q);

    void create_union(int p, int q);

    void validate(int p);
};

void simple_union_find();

#endif //ALGS_CPP_UNION_FIND_H
