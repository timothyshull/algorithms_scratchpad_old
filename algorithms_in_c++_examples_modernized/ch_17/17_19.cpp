template<class Graph>
int ePATH<Graph>::tour(int v)
{
    while (true) {
        typename Graph::adjIterator A(G, v);
        int w = A.beg();
        if (A.end()) { break; }
        S.push(v);
        G.remove(Edge(v, w));
        v = w;
    }
    return v;
}

template<class Graph>
void ePATH<Graph>::show()
{
    if (!found) { return; }
    while (tour(v) == v && !S.empty()) {
        v = S.pop();
        std::cout << "-" << v;
    }
    std::cout << "\n";
}


