#include <iostream>
#include <vector>

static const int max_size = 10000;

int main(int argc, char* argv[])
{
    std::string p{argv[1]};
    std::string a;
    a.reserve(max_size);

    int i;
    char t;
    for (i = 0; i < max_size; a += t, ++i) {
        if (!std::cin.get(t)) { break; }
    }

    a.shrink_to_fit();

    int j;
    for (i = 0; i < a.size(); ++i) {
        for (j = 0; j < p.size(); ++j) {
            if (a[i + j] != p[j]) { break; }
        }
        if (j == p.size()) { std::cout << "The string " << p << " occurred at index " << i << " "; }
    }
    std::cout << "\n";
    return 0;
}

