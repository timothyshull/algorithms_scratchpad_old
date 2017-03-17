// See Sparse_multigraph.h and Sparse_multigraph.cpp

//class Sparse_multigraph_iterator {
//    using link = typename Sparse_multigraph::link;
//
//    const Sparse_multigraph& g;
//    int v;
//    link t;
//public:
//    Sparse_multigraph_iterator(const Sparse_multigraph& graph, int v);
//
//    int begin();
//
//    int next();
//
//    bool end();
//};
//
//Sparse_multigraph_iterator::Sparse_multigraph_iterator(const Sparse_multigraph& graph, int v)
//        : g{graph}, v{v}, t{nullptr} {}
//
//int Sparse_multigraph_iterator::begin()
//{
//    t = g.adj[v];
//    return t ? t->v : -1;
//}
//
//int Sparse_multigraph_iterator::next()
//{
//    if (t) { t = t->next; }
//    return t ? t->v : -1;
//}
//
//bool Sparse_multigraph_iterator::end() { return t == 0; }