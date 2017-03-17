void scR(int w)
{
    int v;
    pre[w] = ++cnt;
    S.push(w);
    path.push(w);
    typename Graph::adjIterator A(G, w);
    for (int t = A.beg(); !A.end(); t = A.nxt()) {
        if (pre[t] == -1) { scR(t); }
        else if (id[t] == -1) {
            while (pre[path.top()] > pre[t]) { path.pop(); }
        }
    }
    if (path.top() == w) { path.pop(); } else { return; }
    do { id[v = S.pop()] = scnt; } while (v != w);
    ++scnt;
}

