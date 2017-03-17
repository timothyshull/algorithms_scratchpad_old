template<class Graph, class Edge> class MAXFLOW {
    const Graph& G;
    int s, t;
    vector<int> wt;
    vector<Edge*> st;

    int ST(int v) const { return st[v]->other(v); }

    void augment(int s, int t)
    {
        int d = st[t]->capRto(t);
        for (int v = ST(t); v != s; v = ST(v)) {
            if (st[v]->capRto(v) < d) {
                d = st[v]->capRto(v);
            }
        }
        st[t]->addflowRto(t, d);
        for (int v = ST(t); v != s; v = ST(v)) {
            st[v]->addflowRto(v, d);
        }
    }

    bool pfs();

public:
    MAXFLOW(const Graph& G, int s, int t) : G(G),
                                            s(s), t(t), st(G.V()), wt(G.V()) { while (pfs()) { augment(s, t); }}
};

