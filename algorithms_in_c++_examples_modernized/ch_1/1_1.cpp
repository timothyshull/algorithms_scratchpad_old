#include <iostream>
#include <vector>

static const int max_size = 10000;

int main()
{
    std::vector<int> id;
    id.reserve(max_size);

    int i;
    for (i = 0; i < max_size; ++i) { id[i] = i; }

    int t;
    int p;
    int q;
    while (std::cin >> p >> q) {
        t = id[p];
        if (t == id[q]) { continue; }
        for (i = 0; i < max_size; ++i) {
            if (id[i] == t) {
                id[i] = id[q];
            }
        }
        std::cout << " " << p << " " << q << "\n";
    }

    return 0;
}

