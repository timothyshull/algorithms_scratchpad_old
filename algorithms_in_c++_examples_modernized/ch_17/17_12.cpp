#include <cstdlib>
#include <random>
#include "Graph.h"

static void random_edges(Graph& graph, int edge)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<> dis(0, RAND_MAX);
    for (int i = 0; i < edge; ++i) {
        int v = int(graph.num_vertices() * dis(gen) / (1.0 + RAND_MAX)); // rand()
        int w = int(graph.num_vertices() * dis(gen) / (1.0 + RAND_MAX)); // rand()
        graph.insert(Edge(v, w));
    }
}

