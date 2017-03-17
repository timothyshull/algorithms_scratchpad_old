#include <iostream>
#include <cstdlib>
#include <vector>
#include "Point.h"

using std::cout;
using std::vector;
using std::size_t;

int main(int argc, char* argv[])
{
    float d = static_cast<float>(atof(argv[2]));
    int i;
    int cnt = 0;
    size_t n = static_cast<size_t>(atoi(argv[1]));
    vector<Point> a{n};
    for (i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i].distance(a[j]) < d) { ++cnt; }
        }
    }
    std::cout << cnt << " pairs within " << d << "\n";
    return 0;
}

