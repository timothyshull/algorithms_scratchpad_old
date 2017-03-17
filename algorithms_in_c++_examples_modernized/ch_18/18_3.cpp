template<class Graph>
class DFS : public SEARCH<Graph> {
    vector<int> st;

    void searchC(Edge e)
    {
        int w = e.w;
        ord[w] = ++cnt;
        st[e.w] = e.v;
        typename Graph::adjIterator A(G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (ord[t] == -1) { searchC(Edge(w, t)); }
        }
    }

public:
    DFS(const Graph& G) : SEARCH<Graph>(G),
                          st(G.V(), -1) { search(); }

    int ST(int v) const { return st[v]; }
};

