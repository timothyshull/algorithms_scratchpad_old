template<class Graph> class ePATH {
    Graph G;
    int v, w;
    bool found;
    STACK<int> S;

    int tour(int v);

public:
    ePATH(const Graph& G, int v, int w) :
            G(G), v(v), w(w)
    {
        DEGREE <Graph> deg(G);
        int t = deg[v] + deg[w];
        if ((t % 2) != 0) {
            found = false;
            return;
        }
        for (t = 0; t < G.V(); ++t) {
            if ((t != v) && (t != w)) {
                if ((deg[t] % 2) != 0) {
                    found = false;
                    return;
                }
            }
        }
        found = true;
    }

    bool exists() const { return found; }

    void show();
};

