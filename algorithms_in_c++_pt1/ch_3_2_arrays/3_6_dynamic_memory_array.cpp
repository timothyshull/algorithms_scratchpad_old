#include <iostream>
#include <new>

int main(int argc, char *argv[]) {
    int i;
    int N = atoi(argv[1]);

    int *a = new(std::nothrow) int[N];
    if (a == nullptr) {
        std::cerr << "operator new with std::nothrow returned nullptr\n";
    }

    try {
        int *b = new int[N];
    } catch (std::bad_alloc &e) {
        std::cerr << "bad_alloc: " << e.what() << "\n";
    }
    return 0;
}
