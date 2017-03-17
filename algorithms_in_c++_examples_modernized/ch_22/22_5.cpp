template<class Graph, class Edge> class MAXFLOW {
    const Graph& G;
    int s, t;
    vector<int> h, wt;

    void initheights();

public:
    MAXFLOW(const Graph& G, int s, int t) : G(G),
                                            s(s), t(t), h(G.V()), wt(G.V(), 0)
    {
        initheights();
        GQ gQ(G.V());
        gQ.put(s);
        wt[t] = -(wt[s] = M * G.V());
        while (!gQ.empty()) {
            int v = gQ.get();
            typename Graph::adjIterator A(G, v);
            for (Edge* e = A.beg(); !A.end(); e = A.nxt()) {
                int w = e->other(v);
                int cap = e->capRto(w);
                int P = cap < wt[v] ? cap : wt[v];
                if (P > 0 && v == s || h[v] == h[w] + 1) {
                    e->addflowRto(w, P);
                    wt[v] -= P;
                    wt[w] += P;
                    if ((w != s) && (w != t)) { gQ.put(w); }
                }
            }
            if (v != s && v != t && wt[v] > 0) {
                ++h[v];
                gQ.put(v);
            }
        }
    }
};

