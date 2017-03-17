#include <iostream>
#include <cmath>

int count_eratosthenes(int N) {
    // have to use long here to avoid integer overflow
    long i;
    int a[N];
    int count = 0;
    for (i = 2; i < N; i++) {
        a[i] = 1;
    }
    for (i = 2; i < N; i++) {
        if (a[i]) {
            // have to use long here to avoid integer overflow resulting in a true check
            for (long j = i; j * i < N; j++) {
                a[i * j] = 0;
            }
        }
    }
    for (i = 2; i < N; i++) {
        if (a[i]) {
            count++;
        }
    }
    return count;
}

int main() {
    int values_to_check[]{
            static_cast<int>(pow(10, 3)),
            static_cast<int>(pow(10, 4)),
            static_cast<int>(pow(10, 5)),
            static_cast<int>(pow(10, 6))
    };

    for (auto i : values_to_check) {
        std::cout << "The number of primes less than " << i << " is " << count_eratosthenes(i) << "\n";
    }
    return 0;
}