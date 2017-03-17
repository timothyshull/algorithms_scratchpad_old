#include "Dense_graph.h"

Dense_graph::Dense_graph(int num_vertices, bool digraph = false)
        : adj{num_vertices}, vertex_cnt{num_vertices}, edge_cnt{0}, digraph{digraph}
{
    for (int i = 0; i < num_vertices; ++i) {
        adj[i].assign(num_vertices, false);
    }
}

int Dense_graph::num_vertices() const { return vertex_cnt; }

int Dense_graph::num_edges() const { return edge_cnt; }

bool Dense_graph::is_directed() const { return digraph; }

void Dense_graph::insert(Edge e)
{
    int v = e.v, w = e.w;
    if (adj[v][w] == false) {
        ++edge_cnt;
    }
    adj[v][w] = true;
    if (!digraph) {
        adj[w][v] = true;
    }
}

void Dense_graph::remove(Edge e)
{
    int v = e.v, w = e.w;
    if (adj[v][w] == true) {
        edge_cnt--;
    }
    adj[v][w] = false;
    if (!digraph) {
        adj[w][v] = false;
    }
}

bool Dense_graph::edge(int v, int w) const
{
    return adj[v][w];
}

int Graph_iterator::begin()
{
    i = -1;
    return next();
}

int Graph_iterator::next()
{
    for
    ++(i;
    i < g.num_vertices();
    ++i) {
        if (g.adj[v][i] == true) { return i; }
    }
    return -1;
}

bool Graph_iterator::end() { return i >= g.num_vertices(); }