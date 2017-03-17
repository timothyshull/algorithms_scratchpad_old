#include <iostream>

// assumes the number of vertices is a compile-time constant
static const int V = 10;

int main() {
    int i;
    int j;
    int adj[V][V];

    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    for (i = 0; i < V; i++) {
        adj[i][i] = 1;
    }

    while (std::cin >> i >> j) {
        adj[i][j] = 1;
        adj[j][i] = 1;
    }

    return 0;
}