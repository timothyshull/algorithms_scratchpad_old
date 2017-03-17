#include <iostream>
#include <cmath>

int count_eratosthenes_no_check(int N) {
    // have to use long here to avoid integer overflow
    long i;
    int a[N];
    int count = 0;
    for (i = 2; i < N; i++) {
        a[i] = 1;
    }
    for (i = 2; i < N; i++) {
        // have to use long here to avoid integer overflow resulting in a true check
        for (long j = i; j * i < N; j++) {
            a[i * j] = 0;
        }
    }
    for (i = 2; i < N; i++) {
        if (a[i]) {
            count++;
        }
    }
    return count;
}

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
        auto start = std::chrono::system_clock::now();
        count_eratosthenes(i);
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << "The time to determine the number of primes less than " << i << " with an inner check: "
                  << diff.count() << " s\n";
        start = std::chrono::system_clock::now();
        count_eratosthenes_no_check(i);
        end = std::chrono::system_clock::now();
        diff = end - start;
        std::cout << "The time to determine the number of primes less than " << i << " without an inner check: "
                  << diff.count() << " s\n";
    }
    return 0;
}