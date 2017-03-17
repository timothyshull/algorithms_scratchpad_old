#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    std::size_t num_vertices{std::stoul(argv[1])};
    std::vector<std::vector<int>> adj{num_vertices, std::vector<int>{num_vertices, 0}};

    int i;
    int j;
    for (i = 0; i < num_vertices; ++i) { adj[i][i] = 1; }
    while (std::cin >> i >> j) {
        adj[i][j] = 1;
        adj[j][i] = 1;
    }
}

