bool searchR(int v, int w, int d)
{
    if (v == w) { return (d == 0); }
    visited[v] = true;
    typename Graph::adjIterator A(G, v);
    for (int t = A.beg(); !A.end(); t = A.nxt()) {
        if (!visited[t]) {
            if (searchR(t, w, d - 1)) { return true; }
        }
    }
    visited[v] = false;
    return false;
}

