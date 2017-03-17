#include "STACK.cc"

template<class Graph> class SC {
    const Graph& G;
    STACK<int> S;
    int cnt, scnt;
    vector<int> pre, low, id;

    void scR(int w)
    {
        int t;
        int min = low[w] = pre[w] = ++cnt;
        S.push(w);
        typename Graph::adjIterator A(G, w);
        for (t = A.beg(); !A.end(); t = A.nxt()) {
            if (pre[t] == -1) { scR(t); }
            if (low[t] < min) { min = low[t]; }
        }
        if (min < low[w]) {
            low[w] = min;
            return;
        }
        do {
            id[t = S.pop()] = scnt;
            low[t] = G.V();
        } while (t != w);
        ++scnt;
    }

public:
    SC(const Graph& G) : G(G), cnt(0), scnt(0),
                         pre(G.V(), -1), low(G.V()), id(G.V())
    {
        for (int v = 0; v < G.V(); ++v) {
            if (pre[v] == -1) { scR(v); }
        }
    }

    int count() const { return scnt; }

    bool stronglyreachable(int v, int w) const { return id[v] == id[w]; }
};

