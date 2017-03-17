template<class Graph> class TC {
    const Graph& G;
    DenseGRAPH* K;
    dagTC <DenseGRAPH, Graph>* Ktc;
    SC <Graph>* Gsc;
public:
    TC(const Graph& G) : G(G)
    {
        Gsc = new SC<Graph>(G);
        K = new DenseGRAPH(Gsc->count(), true);
        for (int v = 0; v < G.V(); ++v) {
            typename Graph::adjIterator A(G, v);
            for (int t = A.beg(); !A.end(); t = A.nxt()) {
                K->insert(Edge(Gsc->ID(v), Gsc->ID(t)));
            }
        }
        Ktc = new dagTC<DenseGRAPH, Graph>(*K);
    }

    ~TC()
    {
        delete K;
        delete Ktc;
        delete Gsc;
    }

    bool reachable(int v, int w) { return Ktc->reachable(Gsc->ID(v), Gsc->ID(w)); }
};


