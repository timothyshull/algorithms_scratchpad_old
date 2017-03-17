#include <vector>

using std::vector;

template<class Edge> class SparseMultiGRAPH {
    int Vcnt, Ecnt;
    bool digraph;

    struct node {
        Edge* e;
        node* next;

        node(Edge* e, node* next) : e(e), next(next) {}
    };

    using link = node*;
    vector<link> adj;
public:
    SparseMultiGRAPH(int V, bool digraph = false) :
            adj(V), Vcnt(V), Ecnt(0), digraph(digraph) {}

    int V() const { return Vcnt; }

    int E() const { return Ecnt; }

    bool directed() const { return digraph; }

    void insert(Edge* e)
    {
        adj[e->v()] = new node(e, adj[e->v()]);
        if (!digraph) {
            adj[e->w()] = new node(e, adj[e->w()]);
        }
        ++Ecnt;
    }

    class Graph_iterator;

    friend class Graph_iterator;
};

