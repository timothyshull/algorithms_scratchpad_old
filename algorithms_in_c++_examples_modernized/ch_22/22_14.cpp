template<class Graph, class Edge> class MINCOST {
    const Graph& G;
    int s, t;
    int valid;
    vector<Edge*> st;
    vector<int> mark, phi;

    void dfsR(Edge);

    int ST(int);

    int phiR(int);

    int lca(int, int);

    Edge* augment(Edge*);

    bool onpath(int, int, int);

    void reverse(int, int);

    void update(Edge*, Edge*);

    int costR(Edge*, int);

    Edge* besteligible();

public:
    MINCOST(Graph& G, int s, int t) : G(G), s(s), t(t)

    st(G
    .

    V()

    ),
    mark(G
    .V(), -1),
    phi(G
    .

    V()

    )
    {
        Edge* z = new EDGE(s, t, M * G.V(), C * G.V());
        G.insert(z);
        z->addflowto(t, z->cap());
        dfsR(z);
        for (valid = 1;; ++valid) {
            phi[t] = z->costRto(s);
            mark[t] = valid;
            for (int v = 0; v < G.V(); ++v) {
                if (v != t) { phi[v] = phiR(v); }
            }
            Edge* x = besteligible();
            if (costR(x, x->v()) == 0) { break; }
            update(augment(x), x);
        }
        G.remove(z);
        delete z;
    }

