#include <vector>

#include "Graph.h"

template<class Graph>
std::vector<Edge> edges(Graph& graph)
{
    int edge = 0;
    std::vector<Edge> edge_vector(graph.num_edges());
    for (int vertex = 0; vertex < graph.num_vertices(); ++vertex) {
        typename Graph::iterator A(graph, vertex);
        for (int w = A.begin(); !A.end(); w = A.next()) {
            if (graph.directed() || vertex < w) {
                ++edge_vector[edge] = Edge(vertex, w);
            }
        }
    }
    return edge_vector;
}