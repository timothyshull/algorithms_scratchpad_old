#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<bool> is_prime{static_cast<unsigned long>(n + 1)};
    for (int i = 2; i <= n; i++) {
        is_prime[i] = true;
    }

    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i; i * j <= n; j++) {
                is_prime[i * j] = false;
            }
        }
    }

    int primes = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) primes++;
    }
    std::cout << "The number of primes <= " << n << " is " << primes;

    // Concise version
    /*int N;
    std::cin >> N;
    int i, a[N];
    for (i = 2; i < N; i++)
        a[ i] = 1;
    for (i = 2; i < N; i++)
        if (a[i])
            for (int j = i; j* i < N; j++)
                a[i * j] = 0;
    for (i = 2; i < N; i++)
        if (a[i])
            std::cout << " " << i;
    std::cout << std::endl;*/
}