template<class inGraph, class outGraph>
void reverse(const inGraph& G, outGraph& R)
{
    for (int v = 0; v < G.V(); ++v) {
        typename inGraph::adjIterator A(G, v);
        for (int w = A.beg(); !A.end(); w = A.nxt()) {
            R.insert(Edge(w, v));
        }
    }
}

