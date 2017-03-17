template<class Graph, class Edge> class allSP {
    const Graph& G;
    vector <vector<Edge*>> p;
    vector <vector<double>> d;
public:
    allSP(const Graph& G) : G(G), p(G.V()), d(G.V())
    {
        int V = G.V();
        for (int i = 0; i < V; ++i) {
            p[i].assign(V, 0);
            d[i].assign(V, V);
        }
        for (int s = 0; s < V; ++s) {
            for (int t = 0; t < V; ++t) {
                if (G.edge(s, t)) {
                    p[s][t] = G.edge(s, t);
                    d[s][t] = G.edge(s, t)->wt();
                }
            }
        }
        for (int s = 0; s < V; ++s) { d[s][s] = 0; }
        for (int i = 0; i < V; ++i) {
            for (int s = 0; s < V; ++s) {
                if (p[s][i]) {
                    for (int t = 0; t < V; ++t) {
                        if (s != t) {
                            if (d[s][t] > d[s][i] + d[i][t]) {
                                p[s][t] = p[s][i];
                                d[s][t] = d[s][i] + d[i][t];
                            }
                        }
                    }
                }
            }
        }
    }

    Edge* path(int s, int t) const { return p[s][t]; }

    double dist(int s, int t) const { return d[s][t]; }
};

