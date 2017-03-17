#include <iostream>
#include <cstdlib>
#include <cmath>

typedef int Number;

Number randNum() {
    return rand() % 2;
}

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);

    float m1 = 0.0;
    float m2 = 0.0;

    for (int i = 0; i < N; i++) {
        Number x = randNum();
        m1 += ((float) x) / N;
        m2 += ((float) x * x) / N;
    }

    std::cout << "    Avg.: " << m1 << "\n";
    std::cout << "Std. dev.: " << sqrt(m2 - m1 * m1) << "\n";

    return 0;
}
