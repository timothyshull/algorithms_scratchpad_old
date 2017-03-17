#ifndef ALGS_CPP_UNION_FIND_H
#define ALGS_CPP_UNION_FIND_H

#include <vector>
#include <bitset>

using std::vector;
using std::bitset;

class pc_uf {
private:
    vector<int> parent;
    vector<int> rank;
    int count;
public:
    pc_uf(int n);

    int find(int p);

    inline int get_count() { return count; }

    bool connected(int p, int q);

    void create_union(int p, int q);

    void validate(int p);

};

void path_compression_uf();

#endif //ALGS_CPP_UNION_FIND_H
