#include "Sparse_multigraph.h"

Sparse_multigraph::Sparse_multigraph(int v, bool digraph = false) :
        adj{v}, vertex_cnt{v}, edge_cnt{0}, digraph{digraph} { adj.assign(v, 0); }

int Sparse_multigraph::num_vertices() const { return vertex_cnt; }

int Sparse_multigraph::num_edges() const { return edge_cnt; }

bool Sparse_multigraph::is_directed() const { return digraph; }

void Sparse_multigraph::insert(Edge e)
{
    int v = e.v, w = e.w;
    adj[v] = new node(w, adj[v]);
    if (!digraph) {
        adj[w] = new node(v, adj[w]);
    }
    ++edge_cnt;
}

void Sparse_multigraph::remove(Edge e);

bool Sparse_multigraph::edge(int v, int w) const;

Sparse_multigraph_iterator::Sparse_multigraph_iterator(const Sparse_multigraph& graph, int v)
        : g{graph}, v{v}, t{nullptr} {}

int Sparse_multigraph_iterator::begin()
{
    t = g.adj[v];
    return t ? t->v : -1;
}

int Sparse_multigraph_iterator::next()
{
    if (t) { t = t->next; }
    return t ? t->v : -1;
}

bool Sparse_multigraph_iterator::end() { return t == 0; }