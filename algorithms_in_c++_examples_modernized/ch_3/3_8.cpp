#include <cmath>
#include <iostream>
#include <random>
#include "Point.h"

float rand_float()
{
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_real_distribution<float> uniform_dist{0, std::numeric_limits<float>::max()};
    return uniform_dist(gen);
}

int main(int argc, char* argv[])
{
    double d{std::stod(argv[2])};

    std::size_t n{std::stoul(argv[1])};
    std::vector<Point> a{n};

    int i;
    for (i = 0; i < n; ++i) {
        a[i].x = rand_float();
        a[i].y = rand_float();
    }

    int cnt{0};
    for (i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (distance(a[i], a[j]) < d) { ++cnt; }
        }
    }
    std::cout << cnt << " pairs within " << d << "\n";
    return 0;
}

