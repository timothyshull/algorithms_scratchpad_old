#include <iostream>
#include <cstdlib>
#include "POINT.h"

int main(int argc, char *argv[]) {
    float d = (float) atof(argv[2]);
    int i, cnt = 0, N = atoi(argv[1]);
    POINT *a = new POINT[N];

    for (i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (a[i].distance(a[j]) < d) cnt++;
        }
    }
    std::cout << cnt << " pairs within " << d << "\n";

    return 0;
}
