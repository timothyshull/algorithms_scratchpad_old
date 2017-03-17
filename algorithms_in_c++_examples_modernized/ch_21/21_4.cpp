#include "SPT.cc"

template<class Graph, class Edge> class allSP {
    const Graph& G;
    vector<SPT < Graph, Edge> *>
    A;
public:
    allSP(const Graph& G) : G(G), A(G.V())
    {
        for (int s = 0; s < G.V(); ++s) {
            A[s] = new SPT<Graph, Edge>(G, s);
        }
    }

    Edge* pathR(int s, int t) const { return A[s]->pathR(t); }

    double dist(int s, int t) const { return A[s]->dist(t); }
};

