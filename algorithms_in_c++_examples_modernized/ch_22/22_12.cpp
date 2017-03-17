bool onpath(int a, int b, int c)
{
    for (int i = a; i != c; i = ST(i)) {
        if (i == b) { return true; }
    }
    return false;
}

void reverse(int u, int x)
{
    Edge* e = st[u];
    for (int i = ST(u); i != x; i = ST(i)) {
        Edge* y = st[i];
        st[i] = e;
        e = y;
    }
}

void update(Edge* w, Edge* y)
{
    int u = y->w(), v = y->v(), x = w->w();
    if (st[x] != w) { x = w->v(); }
    int r = lca(u, v);
    if (onpath(u, x, r)) {
        reverse(u, x);
        st[u] = y;
        return;
    }
    if (onpath(v, x, r)) {
        reverse(v, x);
        st[v] = y;
        return;
    }
}

