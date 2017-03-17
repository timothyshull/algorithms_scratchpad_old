template<class Graph, class Edge> class SPall {
public:
    SPall(const Graph&);

    Edge* path(int, int) const;

    Edge* pathR(int, int) const;

    double dist(int, int) const;
};

