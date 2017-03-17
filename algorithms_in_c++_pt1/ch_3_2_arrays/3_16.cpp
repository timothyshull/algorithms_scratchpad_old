#include <istream>

int count_values(std::istream &in) {
    int test;
    int count = 0;
    while (in >> test) {
        if (test < 1000 && test % 2 == 0) {
            count++;
        }
    }
    return count;
}