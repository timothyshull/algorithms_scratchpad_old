#ifndef GRAPH_H
#define GRAPH_H

struct Edge {
    int v;
    int w;

    Edge(int v = -1, int w = -1) : v{v}, w{w} {}
};

class Graph {
private:
    // Implementation-dependent code
public:
    Graph(int, bool = false);

    ~Graph();

    int num_vertices() const;

    int num_edges() const;

    bool directed() const;

    int insert(Edge);

    int remove(Edge);

    bool edge(int, int);

    class Graph_iterator {
    public:
        Graph_iterator(const Graph&, int);

        int begin();

        int next();

        bool end();
    };

    using iterator = Graph_iterator;

    iterator begin();

    iterator end();
};

#endif //GRAPH_H
