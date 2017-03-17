#include <iostream>

template <typename Item, typename std::enable_if<std::is_signed<Item>::value>::type>
Item lg(Item &n) {
    int i;
    for (i = 0; n > 0; i++, n /= 2) {}
    return i;
}

int main() {
    for (int n = 1000; n <= 1000000000; n *= 10) {
        std::cout << lg(n) << " " << n << "\n";
    }

    return 0;
}

