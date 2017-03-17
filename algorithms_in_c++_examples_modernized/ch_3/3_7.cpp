#include <iostream>
#include <vector>
#include <random>

bool heads()
{
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<int> uniform_dist{0, std::numeric_limits<int>::max()};
    return uniform_dist(gen) < std::numeric_limits<int>::max() / 2;
}

int main(int argc, char* argv[])
{
    int n{std::stoi(argv[1])};
    int m{std::stoi(argv[2])};
    std::vector<int> f{static_cast<std::vector<int>::size_type>(n + 1), 0};

    int i;
    int j;
    int cnt;
    for (i = 0; i < m; ++i, ++f[cnt]) {
        for (cnt = 0, j = 0; j <= n; ++j) {
            if (heads()) { ++cnt; }
        }
    }

    for (j = 0; j <= n; ++j) {
        if (f[j] == 0) { std::cout << "."; }
        for (i = 0; i < f[j]; i += 10) { std::cout << "*"; }
        std::cout << "\n";
    }
    return 0;
}

