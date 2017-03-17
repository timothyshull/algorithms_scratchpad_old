#include "QUEUE.cc"

template<class Graph>
class BFS : public SEARCH<Graph> {
    vector<int> st;

    void searchC(Edge e)
    {
        QUEUE <Edge> Q;
        Q.put(e);
        while (!Q.empty()) {
            if (ord[(e = Q.get()).w] == -1) {
                int v = e.v, w = e.w;
                ord[w] = ++cnt;
                st[w] = v;
                typename Graph::adjIterator A(G, w);
                for (int t = A.beg(); !A.end(); t = A.nxt()) {
                    if (ord[t] == -1) { Q.put(Edge(w, t)); }
                }
            }
        }
    }

public:
    BFS(Graph& G) : SEARCH<Graph>(G), st(G.V(), -1) { search(); }

    int ST(int v) const { return st[v]; }
};

