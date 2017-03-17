int lca(int v, int w)
{
    mark[v] = ++valid;
    mark[w] = valid;
    while (v != w) {
        if (v != t) { v = ST(v); }
        if (v != t && mark[v] == valid) { return v; }
        mark[v] = valid;
        if (w != t) { w = ST(w); }
        if (w != t && mark[w] == valid) { return w; }
        mark[w] = valid;
    }
    return v;
}

Edge* augment(Edge* x)
{
    int v = x->v(), w = x->w();
    int r = lca(v, w);
    int d = x->capRto(w);
    for (int u = w; u != r; u = ST(u)) {
        if (st[u]->capRto(ST(u)) < d) {
            d = st[u]->capRto(ST(u));
        }
    }
    for (int u = v; u != r; u = ST(u)) {
        if (st[u]->capRto(u) < d) {
            d = st[u]->capRto(u);
        }
    }
    x->addflowRto(w, d);
    Edge* e = x;
    for (int u = w; u != r; u = ST(u)) {
        st[u]->addflowRto(ST(u), d);
        if (st[u]->capRto(ST(u)) == 0) { e = st[u]; }
    }
    for (int u = v; u != r; u = ST(u)) {
        st[u]->addflowRto(u, d);
        if (st[u]->capRto(u) == 0) { e = st[u]; }
    }
    return e;
}

