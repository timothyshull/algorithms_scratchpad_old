// See Sparse_multi_graph.h

//#include <vector>
//
//class Graph_iterator;
//
//class Sparse_multigraph {
//    int vertex_cnt;
//    int edge_cnt;
//    bool digraph;
//
//    struct node {
//        int v;
//        node* next;
//
//        node(int x, node* t)
//        {
//            v = x;
//            next = t;
//        }
//    };
//
//    using link = node*;
//    std::vector<link> adj;
//public:
//    Sparse_multigraph(int v, bool digraph = false) :
//            adj{v}, vertex_cnt{v}, edge_cnt{0}, digraph{digraph} { adj.assign(v, 0); }
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
//        adj[v] = new node(w, adj[v]);
//        if (!digraph) { adj[w] = new node(v, adj[w]); }
//        ++edge_cnt;
//    }
//
//    void remove(Edge e);
//
//    bool edge(int v, int w) const;
//
//    friend class Graph_iterator;
//};
