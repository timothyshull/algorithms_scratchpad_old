#include "dagTS.cc"

template<class Graph, class Edge> class LPTdag {
    const Graph& G;
    vector<double> wt;
    vector<Edge*> lpt;
public:
    LPTdag(const Graph& G) : G(G),
                             lpt(G.V()), wt(G.V(), 0)
    {
        int j, w;
        dagTS <Graph> ts(G);
        for (int v = ts[j = 0]; j < G.V(); v = ++ts[j]) {
            typename Graph::adjIterator A(G, v);
            for (Edge* e = A.beg(); !A.end(); e = A.nxt()) {
                if (wt[w = e->w()] < wt[v] + e->wt()) {
                    wt[w] = wt[v] + e->wt();
                    lpt[w] = e;
                }
            }
        }
    }

    Edge* pathR(int v) const { return lpt[v]; }

    double dist(int v) const { return wt[v]; }
};

