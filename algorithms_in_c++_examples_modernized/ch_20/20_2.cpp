template<class Graph, class Edge>
vector<Edge*> edges(const Graph& G)
{
    int E = 0;
    vector < Edge * > a(G.E());
    for (int v = 0; v < G.V(); ++v) {
        typename Graph::adjIterator A(G, v);
        for (Edge* e = A.beg(); !A.end(); e = A.nxt()) {
            if (e->from(v)) { ++a[E] = e; }
        }
    }
    return a;
}

