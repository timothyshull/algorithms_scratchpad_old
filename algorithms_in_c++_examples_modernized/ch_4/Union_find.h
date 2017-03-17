#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <vector>

class Union_find {
private:
    std::vector<int> id;
    std::vector<int> sz;

    int find(int x);

public:
    Union_find(int n);

    bool find(int p, int q);

    void unite(int p, int q);

    {
        int i = find(p), j = find(q);
        if (i == j) { return; }
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
        } else {
            id[j] = i;
            sz[i] += sz[j];
        }
    }
};

#endif //UNION_FIND_H
