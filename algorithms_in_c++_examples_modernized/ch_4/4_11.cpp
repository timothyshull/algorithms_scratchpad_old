class UF {
private:
    int* id, * sz;

    int find(int x)
    {
        while (x != id[x]) { x = id[x]; }
        return x;
    }

public:
    UF(int N)
    {
        id = new int[N];
        sz = new int[N];
        for (int i = 0; i < N; ++i) {
            id[i] = i;
            sz[i] = 1;
        }
    }

    int find(int p, int q) { return (find(p) == find(q)); }

    void unite(int p, int q)
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

