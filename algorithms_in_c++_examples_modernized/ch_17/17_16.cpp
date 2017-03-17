template<class Graph> class sPATH {
    const Graph& G;
    vector<bool> visited;
    bool found;

    bool searchR(int v, int w)
    {
        if (v == w) { return true; }
        visited[v] = true;
        typename Graph::adjIterator A(G, v);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (!visited[t]) {
                if (searchR(t, w)) { return true; }
            }
        }
        return false;
    }

public:
    sPATH(const Graph& G, int v, int w) :
            G(G), visited(G.V(), false) { found = searchR(v, w); }

    bool exists() const { return found; }
};

