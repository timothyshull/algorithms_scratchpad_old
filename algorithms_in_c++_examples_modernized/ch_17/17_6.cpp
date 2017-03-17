#include <iostream>
#include <cstdlib>
#include "Graph.h"
#include "IO.h"
#include "Connected_component.h"

int main(int argc, char* argv[])
{
    int num_vertices = atoi(argv[1]);
    Graph graph{num_vertices};
    IO<Graph>::scan(graph);

    if (num_vertices < 20) {
        IO<Graph>::show(graph);
    }

    std::cout << graph.num_edges() << " edges ";
    Connected_component<Graph> gcc{graph};
    std::cout << gcc.count() << " components" << "\n";

    return 0;
}

