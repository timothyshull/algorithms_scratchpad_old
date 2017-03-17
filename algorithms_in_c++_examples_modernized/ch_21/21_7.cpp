template<class Graph, class Edge> class allSPdag {
    const Graph& G;
    vector <vector<Edge*>> p;
    vector <vector<double>> d;

    void dfsR(int s)
    {
        typename Graph::adjIterator A(G, s);
        for (Edge* e = A.beg(); !A.end(); e = A.nxt()) {
            int t = e->w();
            double w = e->wt();
            if (d[s][t] > w) {
                d[s][t] = w;
                p[s][t] = e;
            }
            if (p[t][t] == 0) { dfsR(t); }
            for (int i = 0; i < G.V(); ++i) {
                if (p[t][i]) {
                    if (d[s][i] > w + d[t][i]) {
                        d[s][i] = w + d[t][i];
                        p[s][i] = e;
                    }
                }
            }
        }
    }

public:
    allSPdag(const Graph& G) : G(G),
                               p(G.V()), d(G.V())
    {
        int V = G.V();
        for (int i = 0; i < V; ++i) {
            p[i].assign(V, 0);
            d[i].assign(V, V);
        }
        for (int s = 0; s < V; ++s) {
            if (p[s][s] == 0) { dfsR(s); }
        }
    }

    Edge* path(int s, int t) const { return p[s][t]; }

    double dist(int s, int t) const { return d[s][t]; }
};

