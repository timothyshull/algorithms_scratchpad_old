#include <iostream>
#include <vector>

static const int max_size = 1000;

int main()
{
    std::vector<int> a;
    a.reserve(max_size);

    int i;
    for (i = 2; i < max_size; ++i) { a[i] = 1; }

    for (i = 2; i < max_size; ++i) {
        if (a[i]) {
            for (int j = i; j * i < max_size; ++j) { a[i * j] = 0; }
        }
    }

    for (i = 2; i < max_size; ++i) {
        if (a[i]) { std::cout << " " << i << "\n"; }
    }
    std::cout << "\n";

    return 0;
}

