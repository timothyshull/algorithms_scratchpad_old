#include <iostream>
#include <random>

template<typename Number = int>
Number random_number()
{
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<Number> uniform_dist{0, std::numeric_limits<Number>::max()};
    return uniform_dist(gen);
}

template<>
float random_number<float>()
{
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_real_distribution<float> uniform_dist{0, std::numeric_limits<float>::max()};
    return uniform_dist(gen);
}

int main(int argc, char* argv[])
{
    int n{std::stoi(argv[1])};
    float m1{0.0};
    float m2{0.0};

    for (int i{0}; i < n; ++i) {
        float x{random_number<float>()};
        m1 += x / n;
        m2 += x * x / n;
    }

    std::cout << "     Avg.: " << m1 << "\n";
    std::cout << "Std. dev.: " << sqrt(m2 - m1 * m1) << "\n";
    return 0;
}

