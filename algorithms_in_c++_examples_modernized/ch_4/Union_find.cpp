#include <vector>
#include "Union_find.h"

using std::vector;

int Union_find::find(int x)
{
    while (x != id[x]) { x = id[x]; }
    return x;
}

Union_find::Union_find(int n) : id{vector<int>{n}}, sz{vector<int>{n}}
{
    for (int i = 0; i < n; ++i) {
        id[i] = i;
        sz[i] = 1;
    }
}

bool Union_find::find(int p, int q) { return (find(p) == find(q)); }

void Union_find::unite(int p, int q)
{
    int i = find(p);
    int j = find(q);
    if (i == j) { return; }
    if (sz[i] < sz[j]) {
        id[i] = j;
        sz[j] += sz[i];
    } else {
        id[j] = i;
        sz[i] += sz[j];
    }
}