#include <iostream>

int lg(int);

int main()
{
    for (int i = 1000; i <= 1000000000; i *= 10) {
        std::cout << lg(i) << " " << i << "\n";
    }
    return 0;
}

int lg(int n)
{
    int i;
    for (i = 0; n > 0; ++i, n /= 2) {}
    return i;
}

