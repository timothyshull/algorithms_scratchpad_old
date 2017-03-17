#include <iostream>

// assumes the number of vertices is a compile-time constant
static const int V = 10;

struct node {
    int v;
    node *next;

    node(int x, node *t) {
        v = x;
        next = t;
    }
};

typedef node *link;

int main() {
    int i;
    int j;
    link adj[V];

    for (i = 0; i < V; i++) {
        adj[i] = 0;
    }

    while (std::cin >> i >> j) {
        adj[j] = new node(i, adj[j]);
        adj[i] = new node(j, adj[i]);
    }

    return 0;
}