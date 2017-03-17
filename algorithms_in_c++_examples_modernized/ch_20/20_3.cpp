template<class Edge> class DenseGRAPH {
    int Vcnt, Ecnt;
    bool digraph;
    vector <vector<Edge*>> adj;
public:
    DenseGRAPH(int V, bool digraph = false) :
            adj(V), Vcnt(V), Ecnt(0), digraph(digraph)
    {
        for (int i = 0; i < V; ++i) {
            adj[i].assign(V, 0);
        }
    }

    int V() const { return Vcnt; }

    int E() const { return Ecnt; }

    bool directed() const { return digraph; }

    void insert(Edge* e)
    {
        int v = e->v(), w = e->w();
        if (adj[v][w] == 0) { ++Ecnt; }
        adj[v][w] = e;
        if (!digraph) { adj[w][v] = e; }
    }

    void remove(Edge* e)
    {
        int v = e->v(), w = e->w();
        if (adj[v][w] != 0) { Ecnt--; }
        adj[v][w] = 0;
        if (!digraph) { adj[w][v] = 0; }
    }

    Edge* edge(int v, int w) const { return adj[v][w]; }

    class Graph_iterator;

    friend class Graph_iterator;
};

