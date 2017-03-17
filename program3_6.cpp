#include <iostream>

int main(int argc, char *argv[]) {
    int i;
    int N = atoi(argv[1]);

    int *a;
    try {
        a = new int[N];
    } catch (std::bad_alloc &e) {
        std::cout << "Unable to allocate memory. Exiting ..." << std::endl;
        exit(1);
    }

    return 0;
}