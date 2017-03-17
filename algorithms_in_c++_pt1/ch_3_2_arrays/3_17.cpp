#include <iostream>

static const int range = 1000;
int counts[range];

int random_in_range() {
    return rand() % range;
}

int count_until_repeat() {
    int count = 0;
    for (int i = 0; i < range; i++) {
        counts[i] = 0;
    }

    int prev_count = 0;
    while (prev_count < 2) {
        prev_count = counts[random_in_range()]++;
        count++;
    }
    return count;
}

int main() {
    for (int i = 0; i < range; i++) {
        std::cout << "The number of random values generated before a repetition on try " << i << " was: " << count_until_repeat() << "\n";
    }

    return 0;
}