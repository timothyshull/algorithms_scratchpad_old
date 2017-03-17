#include <cmath>
#include <iostream>
#include <vector>
#include "point.h"

double rand_float();

double distance(point a, point b);

int main(int argc, char *argv[]) {
    double d = atof(argv[2]);
    int i, cnt = 0, N = atoi(argv[1]);
    std::vector<point<double>> a;
    for (i = 0; i < N; i++) {
        a[i] = point{rand_float(), rand_float()};
    }
    for (i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (distance(a[i], a[j]) < d)
                cnt++;
    std::cout << cnt << " pairs within " << d << std::endl;
}

double rand_float() {
    return 1.0 * rand() / RAND_MAX;
}