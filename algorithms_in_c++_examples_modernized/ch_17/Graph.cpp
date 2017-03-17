#include "Graph.h"

Graph::Graph(int, bool)
{

}

Graph::~Graph()
{

}

int Graph::num_vertices() const
{
    return 0;
}

int Graph::num_edges() const
{
    return 0;
}

bool Graph::directed() const
{
    return false;
}

int Graph::insert(Edge)
{
    return 0;
}

int Graph::remove(Edge)
{
    return 0;
}

bool Graph::edge(int, int)
{
    return false;
}

Graph::iterator Graph::begin()
{
    return Graph::iterator(Graph(), 0);
}

Graph::iterator Graph::end()
{
    return Graph::iterator(Graph(), 0);
}
