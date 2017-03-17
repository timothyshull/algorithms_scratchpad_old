#include "MAXFLOW.cc"

template<class Graph, class Edge> class FEASIBLE {
    const Graph& G;

    void freeedges(const Graph& F, int v)
    {
        typename Graph::adjIterator A(F, v);
        for (EDGE* e = A.beg(); !A.end(); e = A.nxt()) {
            delete e;
        }
    }

public:
    FEASIBLE(const Graph& G, vector<int> sd) : G(G)
    {
        Graph F(G.V() + 2);
        for (int v = 0; v < G.V(); ++v) {
            typename Graph::adjIterator A(G, v);
            for (EDGE* e = A.beg(); !A.end(); e = A.nxt()) {
                F.insert(e);
            }
        }
        int s = G.V(), t = G.V() + 1;
        for (int i = 0; i < G.V(); ++i) {
            if (sd[i] >= 0) {
                F.insert(new EDGE(s, i, sd[i]));
            } else {
                F.insert(new EDGE(i, t, -sd[i]));
            }
        }
        MAXFLOW<Graph, Edge>(F, s, t);
        freeedges(F, s);
        freeedges(F, t);
    }
};

