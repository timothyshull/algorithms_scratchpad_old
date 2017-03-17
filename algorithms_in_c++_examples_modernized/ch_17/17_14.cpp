#include "ST.cc"

template<class Graph>
void IO<Graph>::scan(Graph& G)
{
    string v, w;
    ST st;
    while (std::cin >> v >> w) {
        G.insert(Edge(st.index(v), st.index(w)));
    }
}

