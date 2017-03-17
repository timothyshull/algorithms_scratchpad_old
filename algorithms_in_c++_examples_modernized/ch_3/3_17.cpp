#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    const std::size_t n_max{1000};
    std::vector<std::string> a;
    a.reserve(n_max);

    int n;
    std::string line;
    for (n = 0; n < n_max; ++n) {
        std::getline(std::cin, line);
        if (!line.empty()) {
            a[n] = line;
        } else {
            break;
        }
    }

    std::sort(a.begin(), a.end(), std::lexicographical_compare);
    for (auto s : a) {
        std::cout << s << "\n";
    }
    return 0;
}

