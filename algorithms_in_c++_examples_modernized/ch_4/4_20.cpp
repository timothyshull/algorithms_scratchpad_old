#include <iostream>
#include <stdlib.h>
#include "Queue.h"

using std::cout;

static const int M = 4;

int main(int argc, char* argv[])
{
    int N = atoi(argv[1]);
    Queue<int> queues[M];
    for (int i = 0; i < N; ++i, std::cout << "\n") {
        int in = rand() % M, out = rand() % M;
        queues[in].put(i);
        std::cout << i << " in ";
        if (!queues[out].empty()) {
            std::cout << queues[out].get() << " out";
        }
        std::cout << "\n";
        for (int k = 0; k < M; ++k, std::cout << "\n") {
            QUEUE<int> q = queues[k];
            std::cout << k << ": ";
            while (!q.empty()) {
                std::cout << q.get() << " ";
            }
        }
    }
    return 0;
}

