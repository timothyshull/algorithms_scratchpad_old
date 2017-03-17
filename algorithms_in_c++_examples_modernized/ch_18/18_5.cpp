template<class Graph>
class EULER : public SEARCH<Graph> {
    void searchC(Edge e)
    {
        int v = e.v, w = e.w;
        ord[w] = ++cnt;
        std::cout << "-" << w;
        typename Graph::adjIterator A(G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (ord[t] == -1) { searchC(Edge(w, t)); }
            else if (ord[t] < ord[v]) {
                std::cout << "-" << t << "-" << w;
            }
        }
        if (v != w) { std::cout << "-" << v; } else { std::cout << "\n"; }
    }

public:
    EULER(const Graph& G) : SEARCH<Graph>(G) { search(); }
};


