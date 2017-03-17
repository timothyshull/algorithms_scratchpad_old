#include <iostream>
#include <vector>

static const int max_size = 10000;

int main()
{
    std::vector<int> id;
    id.reserve(max_size);

    int i;
    for (i = 0; i < max_size; ++i) { id[i] = i; }

    int p;
    int q;
    int j;
    while (std::cin >> p >> q) {
        for (i = p; i != id[i]; i = id[i]) {}
        for (j = q; j != id[j]; j = id[j]) {}

        if (i == j) { continue; }
        id[i] = j;
        std::cout << " " << p << " " << q << "\n";
    }
    return 0;
}