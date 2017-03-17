template<class Graph, class Edge> class MST {
    const Graph& G;
    vector<double> wt;
    vector<Edge*> fr, mst;
public:
    MST(const Graph& G) : G(G),
                          mst(G.V()), wt(G.V(), G.V()), fr(G.V())
    {
        int min = -1;
        for (int v = 0; min != 0; v = min) {
            min = 0;
            for (int w = 1; w < G.V(); ++w) {
                if (mst[w] == 0) {
                    double P;
                    Edge* e = G.edge(v, w);
                    if (e) {
                        if ((P = e->wt()) < wt[w]) {
                            wt[w] = P;
                            fr[w] = e;
                        }
                    }
                    if (wt[w] < wt[min]) { min = w; }
                }
            }
            if (min) { mst[min] = fr[min]; }
        }
    }

    void show()
    {
        for (int v = 1; v < G.V(); ++v) {
            if (mst[v]) { mst[v]->show(); }
        }
    }
};

