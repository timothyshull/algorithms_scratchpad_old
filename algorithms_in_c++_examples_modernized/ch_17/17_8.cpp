// See Dense_graph.h

//#include "Dense_graph.h"
//
//class Graph_iterator {
//    const Dense_graph& g;
//    int i;
//    int v;
//public:
//    Graph_iterator(const Dense_graph& graph, int v) : g{graph}, v{v}, i{-1} {}
//
//    int begin()
//    {
//        i = -1;
//        return next();
//    }
//
//    int next()
//    {
//        for ++(i; i < g.num_vertices(); ++i) {
//            if (g.adj[v][i] == true) { return i; }
//        }
//        return -1;
//    }
//
//    bool end() { return i >= g.num_vertices(); }
//};
