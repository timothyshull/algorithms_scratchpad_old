void searchC(Edge e)
{
    QUEUE <Edge> Q;
    Q.put(e);
    ord[e.w] = ++cnt;
    while (!Q.empty()) {
        e = Q.get();
        st[e.w] = e.v;
        typename Graph::adjIterator A(G, e.w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (ord[t] == -1) {
                Q.put(Edge(e.w, t));
                ord[t] = ++cnt;
            }
        }
    }
}

