#include "GRAPHbasic.cc"
#include "GRAPHio.cc"
#include "LPTdag.cc"

using Edge = Weighted_edge;

using Graph = Dense_graph<Edge>;

int main(int argc, char* argv[])
{
    int i, s, t, N = atoi(argv[1]);
    double duration[N];
    Graph G(N, true);
    for (int i = 0; i < N; ++i) {
        std::cin >> duration[i];
    }
    while (std::cin >> s >> t) {
        G.insert(new Edge(s, t, duration[s]));
    }
    LPTdag <Graph, Edge> lpt(G);
    for (i = 0; i < N; ++i) {
        std::cout << i << " " << lpt.dist(i) << "\n";
    }
}

