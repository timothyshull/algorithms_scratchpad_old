template<class Graph, class Edge, class EdgePtr>
class MST {
    const Graph& G;
    vector <EdgePtr> a, mst;
    UF uf;
public:
    MST(Graph& G) : G(G), uf(G.V()), mst(G.V())
    {
        int V = G.V(), E = G.E();
        a = edges<Graph, Edge, EdgePtr>(G);
        sort<EdgePtr>(a, 0, E - 1);
        for (int i = 0, k = 1; i < E && k < V; ++i) {
            if (!uf.find(a[i]->v, a[i]->w)) {
                uf.unite(a[i]->v, a[i]->w);
                ++mst[k] = a[i];
            }
        }
    }
};

