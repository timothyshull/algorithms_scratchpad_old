int costR(Edge* e, int v)
{
    int R = e->cost() + phi[e->w()] - phi[e->v()];
    return e->from(v) ? R : -R;
}

Edge* besteligible()
{
    Edge* x = 0;
    for (int v = 0, min = C * G.V(); v < G.V(); ++v) {
        typename Graph::adjIterator A(G, v);
        for (Edge* e = A.beg(); !A.end(); e = A.nxt()) {
            if (e->capRto(e->other(v)) > 0) {
                if (e->capRto(v) == 0) {
                    if (costR(e, v) < min) {
                        x = e;
                        min = costR(e, v);
                    }
                }
            }
        }
    }
    return x;
}

