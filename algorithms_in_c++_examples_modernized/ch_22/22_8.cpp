static int cost(Graph& G)
{
    int x = 0;
    for (int v = 0; v < G.V(); ++v) {
        typename Graph::adjIterator A(G, v);
        for (Edge* e = A.beg(); !A.end(); e = A.nxt()) {
            if (e->from(v) && e->costRto(e->w()) < C) {
                x += e->flow() * e->costRto(e->w());
            }
        }
    }
    return x;
}

