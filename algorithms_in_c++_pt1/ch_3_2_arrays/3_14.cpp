#include <iostream>
#include <vector>

static const int N = 1000;

void eratosthenes_vector() {
    int i;
    std::vector<int>a;
    a.reserve(N);

    for (i = 2; i < N; i++) {
        a[i] = 1;
    }

    for (i = 2; i < N; i++) {
        if (a[i]) {
            for (int j = i; j * i < N; j++) {
                a[i * j] = 0;
            }
        }
    }

    for (i = 2; i < N; i++) {
        if (a[i]) {
            std::cout << " " << i;
        }
    }
    std::cout << "\n";
}

int main() {
    eratosthenes_vector();

    return 0;
}