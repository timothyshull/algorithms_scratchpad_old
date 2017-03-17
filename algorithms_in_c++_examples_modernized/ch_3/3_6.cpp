#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    std::size_t n{std::stoul(argv[1])};
    std::vector<int> a;
    a.reserve(n);
    if (a.capacity() != a) {
        std::cout << "unable to reserve memory for size " << n << "\n";
        return -1;
    }
    // ...
    return 0;
}
