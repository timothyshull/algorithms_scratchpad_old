template<class Edge>
class DenseGRAPH<Edge>::adjIterator {
    const DenseGRAPH<Edge>& G;
    int i, v;
public:
    adjIterator(const DenseGRAPH<Edge>& G, int v) :
            G(G), v(v), i(0) {}

    Edge* beg()
    {
        i = -1;
        return nxt();
    }

    Edge* nxt()
    {
        for
        ++(i;
        i < G.V();
        ++i) {
            if (G.edge(v, i)) { return G.adj[v][i]; }
        }
        return 0;
    }

    bool end() const { return i >= G.V(); }
};

