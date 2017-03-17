#include <iostream>
#include <cmath>
#include <vector>

int randNum(int range) {
    return rand() % range;
}

void avgAndStdDev(int range, int N) {
    float m1 = 0.0;
    float m2 = 0.0;

    for (int i = 0; i < N; i++) {
        int x = randNum(range);
        m1 += ((float) x) / N;
        m2 += ((float) x * x) / N;
    }

    std::cout << "For a range of " << range << " and computing " << N << " repetitions: \n";
    std::cout << "    Avg.: " << m1 << "\n";
    std::cout << "Std. dev.: " << sqrt(m2 - m1 * m1) << "\n";
}

int powerOfTen(int power) {
    // assumes power is at least 1
    int accumulator = 10;
    for (int i = 2; i <= power; i++) {
        accumulator *= 10;
    }
    return accumulator;
}

int main(int argc, char *argv[]) {
    std::vector<int> ranges{10, 100, 1000};
    std::vector<int> repetitions{powerOfTen(3), powerOfTen(4), powerOfTen(5), powerOfTen(6)};

    for (auto r : ranges) {
        for (auto N : repetitions) {
            avgAndStdDev(r, N);
        }
    }

    return 0;
}