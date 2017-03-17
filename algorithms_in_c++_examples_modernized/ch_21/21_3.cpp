template<class Graph, class Edge>
double diameter(Graph& G)
{
    int vmax = 0, wmax = 0;
    allSP <Graph, Edge> all(G);
    for (int v = 0; v < G.V(); ++v) {
        for (int w = 0; w < G.V(); ++w) {
            if (all.path(v, w)) {
                if (all.dist(v, w) > all.dist(vmax, wmax)) {
                    vmax = v;
                    wmax = w;
                }
            }
        }
    }
    int v = vmax;
    std::cout << v;
    while (v != wmax) {
        v = all.path(v, wmax)->w();
        std::cout << "-" << v;
    }
    return all.dist(vmax, wmax);
}

