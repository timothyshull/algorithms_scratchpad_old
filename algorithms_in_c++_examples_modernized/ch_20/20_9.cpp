template<class Graph, class Edge> class MST {
    const Graph& G;
    vector<Edge*> a, b, mst;
    UF uf;
public:
    MST(const Graph& G) : G(G), uf(G.V()), mst(G.V() + 1)
    {
        a = edges<Graph, Edge>(G);
        int N, k = 1;
        for (int E = a.size(); E != 0; E = N) {
            int h, i, j;
            b.assign(G.V(), 0);
            for (h = 0, N = 0; h < E; ++h) {
                Edge* e = a[h];
                i = uf.find(e->v()), j = uf.find(e->w());
                if (i == j) { continue; }
                if (!b[i] || e->wt() < b[i]->wt()) { b[i] = e; }
                if (!b[j] || e->wt() < b[j]->wt()) { b[j] = e; }
                ++a[N] = e;
            }
            for (h = 0; h < G.V(); ++h) {
                if (b[h]) {
                    if (!uf.find(i = b[h]->v(), j = b[h]->w())) {
                        uf.unite(i, j);
                        ++mst[k] = b[h];
                    }
                }
            }
        }
    }
};

