#include <iostream>

int heads() {
    return rand() < RAND_MAX / 2;
}

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);

    int *f;
    try {
        f = new int[N + 1];
    } catch (std::bad_alloc &e) {
        std::cout << "Unable to allocate memory. Exiting ..." << std::endl;
        exit(1);
    }

    int j;
    for (j = 0; j <= N; j++)
        f[j] = 0;

    int i;
    int cnt = 0;
    for (i = 0; i < M; i++, f[cnt]++)
        if (heads())
            cnt++;

    for (j = 0; j <= N; j++) {
        if (f[j] == 0)
            std::cout << ".";
        for (i = 0; i < f[j]; i += 10)
            std::cout << "*";
        std::cout << std::endl;
    }

    return 0;
}