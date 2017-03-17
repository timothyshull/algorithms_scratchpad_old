#ifndef SPARSE_MULTI_GRAPH_H
#define SPARSE_MULTI_GRAPH_H

#include <vector>
#include "Graph.h"

class Sparse_multigraph_iterator;

class Sparse_multigraph {
    int vertex_cnt;
    int edge_cnt;
    bool digraph;

    struct node {
        int v;
        node* next;

        node(int x, node* t)
        {
            v = x;
            next = t;
        }
    };

    using link = node*;
    std::vector<link> adj;
public:
    Sparse_multigraph(int v, bool digraph = false);

    int num_vertices() const;

    int num_edges() const;

    bool is_directed() const;

    void insert(Edge e);

    void remove(Edge e);

    bool edge(int v, int w) const;

    friend class Sparse_multigraph_iterator;
};

class Sparse_multigraph_iterator {
    using link = typename Sparse_multigraph::link;

    const Sparse_multigraph& g;
    int v;
    link t;
public:
    Sparse_multigraph_iterator(const Sparse_multigraph& graph, int v);

    int begin();

    int next();

    bool end();
};

#endif //SPARSE_MULTI_GRAPH_H
