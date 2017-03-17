#include <iostream>
#include <bitset>
// use std::bitset
static const int N = 1000;

void eratosthenes_bitset() {
    int i;
    std::bitset<N> a;
    a.flip();
    a.flip(0);
    a.flip(1);

    for (i = 2; i < N; i++) {
        if (a[i]) {
            for (int j = i; j * i < N; j++) {
                a.set(static_cast<size_t>(i * j), false);
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

void eratosthenes_char() {
    int i;
    char a[N];

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
    eratosthenes_bitset();
    eratosthenes_char();

    return 0;
}