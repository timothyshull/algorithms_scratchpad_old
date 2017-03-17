template<class Graph> class SC {
    const Graph& G;
    int cnt, scnt;
    vector<int> postI, postR, id;

    void dfsR(const Graph& G, int w)
    {
        id[w] = scnt;
        typename Graph::adjIterator A(G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (id[t] == -1) { dfsR(G, t); }
        }
        ++postI[cnt] = w;
    }

public:
    SC(const Graph& G) : G(G), cnt(0), scnt(0),
                         postI(G.V()), postR(G.V()), id(G.V(), -1)
    {
        Graph R(G.V(), true);
        reverse(G, R);
        for (int v = 0; v < R.V(); ++v) {
            if (id[v] == -1) { dfsR(R, v); }
        }
        postR = postI;
        cnt = scnt = 0;
        id.assign(G.V(), -1);
        for (int v = G.V() - 1; v >= 0; v--) {
            if (id[postR[v]] == -1) {
                dfsR(G, postR[v]);
                ++scnt;
            }
        }
    }

    int count() const { return scnt; }

    bool stronglyreachable(int v, int w) const { return id[v] == id[w]; }
};

