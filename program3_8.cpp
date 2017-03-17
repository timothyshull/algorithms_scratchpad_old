#include <cmath>
#include <iostream>

struct point {
    double x;
    double y;
};

double rand_float() {
    return 1.0 * rand() / RAND_MAX;
}

double distance(point begin, point end) {
    return sqrt(pow(begin.x - end.x, 2.0) + pow(begin.y - end.y, 2.0));
}

int main(int argc, char *argv[]) {
    double d = atof(argv[2]);
    int cnt = 0;
    int N = atoi(argv[1]);

    point *a;
    try {
        a = new point[N];
    } catch (std::bad_alloc &e) {
        std::cout << "Unable to allocate memory. Exiting ..." << std::endl;
        exit(1);
    }

    int i;
    for (i = 0; i < N; i++) {
        a[i].x = rand_float();
        a[i].y = rand_float();
    }

    for (i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++)
            if (distance(a[i], a[j]) < d)
                cnt++;
    }

    std::cout << cnt << " pairs within " << d << std::endl;

    return 0;
}
