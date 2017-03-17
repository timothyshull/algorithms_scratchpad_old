template<class Graph, class Edge> class MST {
    const Graph& G;
    vector<double> wt;
    vector<Edge*> fr, mst;

    void pfs(int s)
    {
        PQi<double> pQ(G.V(), wt);
        pQ.insert(s);
        while (!pQ.empty()) {
            int v = pQ.getmin();
            mst[v] = fr[v];
            typename Graph::adjIterator A(G, v);
            for (Edge* e = A.beg(); !A.end(); e = A.nxt()) {
                double P = e->wt();
                int w = e->other(v);
                if (fr[w] == 0) {
                    wt[w] = P;
                    pQ.insert(w);
                    fr[w] = e;
                } else if (mst[w] == 0 && P < wt[w]) {
                    wt[w] = P;
                    pQ.lower(w);
                    fr[w] = e;
                }
            }
        }
    }

public:
    MST(Graph& G) : G(G),
                    fr(G.V()), mst(G.V()), wt(G.V(), -1)
    {
        for (int v = 0; v < G.V(); ++v) {
            if (mst[v] == 0) { pfs(v); }
        }
    }
};

