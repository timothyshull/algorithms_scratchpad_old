// See Dense_graph.h

//#include <vector>
//#include <deque>
//#include "Graph.h"
//
//class Edge;
//
//class Dense_graph {
//    int vertex_cnt;
//    int edge_cnt;
//    bool digraph;
//    std::vector<std::deque<bool>> adj; // std::vector<std::vector<bool>> adj; -> to avoid issues with vector<bool>
//public:
//    Dense_graph(int num_vertices, bool digraph = false) : adj(num_vertices), vertex_cnt(num_vertices), edge_cnt(0), digraph(digraph)
//    {
//        for (int i = 0; i < num_vertices; ++i) {
//            adj[i].assign(num_vertices, false);
//        }
//    }
//
//    int num_vertices() const { return vertex_cnt; }
//
//    int num_edges() const { return edge_cnt; }
//
//    bool is_directed() const { return digraph; }
//
//    void insert(Edge e)
//    {
//        int v = e.v, w = e.w;
//        if (adj[v][w] == false) { ++edge_cnt; }
//        adj[v][w] = true;
//        if (!digraph) { adj[w][v] = true; }
//    }
//
//    void remove(Edge e)
//    {
//        int v = e.v, w = e.w;
//        if (adj[v][w] == true) { edge_cnt--; }
//        adj[v][w] = false;
//        if (!digraph) { adj[w][v] = false; }
//    }
//
//    bool edge(int v, int w) const { return adj[v][w]; }
//
//    class Graph_iterator;
//
//    friend class Graph_iterator;
//};

