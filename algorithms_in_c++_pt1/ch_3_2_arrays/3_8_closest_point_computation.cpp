#include <cmath>
#include <iostream>
#include <cstdlib>
#include "Point.h"

float randFloat() {
    return (float) (1.0 * rand() / RAND_MAX);
}

int main(int argc, char *argv[]) {
    float d = (float) atof(argv[2]);
    int i;
    int cnt = 0;
    int N = atoi(argv[1]);
    point *a = new point[N];

    for (i = 0; i < N; i++) {
        a[i].x = randFloat();
        a[i].y = randFloat();
    }

    for (i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (distance(a[i], a[j]) < d) {
                cnt++;
            }
        }
    }
    std::cout << cnt << " pairs within " << d << "\n";
    return 0;
}