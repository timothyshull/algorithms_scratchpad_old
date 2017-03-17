#include <iostream>
#include <vector>
#include <memory>

#include "list.h"

int main(int argc, char* argv[])
{
    std::size_t num_vertices{std::stoul(argv[1])};
    std::vector<Raw_node_pointer<int>> adj{num_vertices, nullptr};

    int i;
    int j;
    while (std::cin >> i >> j) {
        adj[j] = make_shared(i, adj[j]);
        adj[i] = make_shared(j, adj[i]);
    }
    return 0;
}

