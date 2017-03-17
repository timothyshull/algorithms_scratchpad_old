#ifndef DENSE_GRAPH_H
#define DENSE_GRAPH_H

#include <vector>
#include <deque>
#include "Graph.h"

class Edge;

class Graph_iterator;

class Dense_graph {
    int vertex_cnt;
    int edge_cnt;
    bool digraph;
    std::vector<std::deque<bool>> adj; // std::vector<std::vector<bool>> adj; -> to avoid issues with vector<bool>
public:
    using iterator = Graph_iterator;

    Dense_graph(int num_vertices, bool digraph = false);

    int num_vertices() const;

    int num_edges() const;

    bool is_directed() const;

    void insert(Edge e);

    void remove(Edge e);

    bool edge(int v, int w) const;

    friend class Graph_iterator;
};

class Graph_iterator {
    const Dense_graph& g;
    int i;
    int v;
public:
    Graph_iterator(const Dense_graph& graph, int v) : g{graph}, v{v}, i{-1} {}

    int begin();

    int next();

    bool end();
};

#endif //TMP_DENSE_GRAPH_H
