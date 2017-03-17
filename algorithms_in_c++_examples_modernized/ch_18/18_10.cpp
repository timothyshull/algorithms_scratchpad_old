#include "GQ.cc"

template<class Graph>
class PFS : public SEARCH<Graph> {
    vector<int> st;

    void searchC(Edge e)
    {
        GQ <Edge> Q(G.V());
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
                } else if (st[t] == -1) { Q.update(Edge(e.w, t)); }
            }
        }
    }

public:
    PFS(Graph& G) : SEARCH<Graph>(G), st(G.V(), -1) { search(); }

    int ST(int v) const { return st[v]; }
};


