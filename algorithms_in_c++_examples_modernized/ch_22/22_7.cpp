#include "GRAPHbasic.cc"
#include "MAXFLOW.cc"

int main(int argc, char* argv[])
{
    int s, t, N = atoi(argv[1]);
    GRAPH <EDGE> G(2 * N + 2);
    for (int i = 0; i < N; ++i) {
        G.insert(new EDGE(2 * N, i, 1));
    }
    while (std::cin >> s >> t) {
        G.insert(new EDGE(s, t, 1));
    }
    for (int i = N; i < 2 * N; ++i) {
        G.insert(new EDGE(i, 2 * N + 1, 1));
    }
    MAXFLOW < GRAPH < EDGE > , EDGE > (G, 2 * N, 2 * N + 1);
    for (int i = 0; i < N; ++i) {
        GRAPH<EDGE>::adjIterator A(G, i);
        for (EDGE* e = A.beg(); !A.end(); e = A.nxt()) {
            if (e->flow() == 1 && e->from(i)) {
                std::cout << e->v() << "-" << e->w() << "\n";
            }
        }
    }

}

