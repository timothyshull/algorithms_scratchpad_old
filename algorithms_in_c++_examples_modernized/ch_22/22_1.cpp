template<class Graph, class Edge>
class check {
public:
    static int flow(Graph& G, int v)
    {
        int x = 0;
        typename Graph::adjIterator A(G, v);
        for (Edge* e = A.beg(); !A.end(); e = A.nxt()) {
            x += e->from(v) ? e->flow() : -e->flow();
        }
        return x;
    }

    static bool flow(Graph& G, int s, int t)
    {
        for (int v = 0; v < G.V(); ++v) {
            if ((v != s) && (v != t)) {
                if (flow(G, v) != 0) { return false; }
            }
        }
        int sflow = flow(G, s);
        if (sflow < 0) { return false; }
        if (sflow + flow(G, t) != 0) { return false; }
        return true;
    }
};

