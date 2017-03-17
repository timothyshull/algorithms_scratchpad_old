#include <iostream>
#include <cstdlib>
#include <cmath>

using Number = int;

Number randNum() {
    return rand();
}

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);
    float m1 = 0.0;
    float m2 = 0.0;

    for (int i = 0; i < N; i++) {
        Number x = randNum();
        m1 += static_cast<float>(x) / N;
        m2 += static_cast<float>(x * x) / N;
    }

    std::cout << "Avg: " << m1 << std::endl;
    std::cout << "Std deviation: " << sqrt(m2 - m1 * m1) << std::endl;

    return 0;
}