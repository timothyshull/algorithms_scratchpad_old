// std_dev = sqrt(1/N * sum((xsubi - mean) ^ 2))

#include <cstddef>
#include <cstdlib>
#include <cmath>
#include <iostream>

// mean has int overflow issues

static const int MAX_N = 10000000;
static const int RAND_RANGE = 1000;

int get_rand(int range) {
    return static_cast<int>(rand() * (range / static_cast<double>(RAND_MAX)));
}

double mean(int nums[], size_t N) {
    int acc = 0;

    for (int i = 0; i < N; i++) {
        acc += nums[i];
    }

    return static_cast<double>(acc) / N;
}

double std_dev(double mean, int nums[], size_t N) {
    double acc = 0;

    for (int i = 0; i < N; i++) {
        acc += pow(nums[i] - mean, 2);
    }

    return sqrt((1 / static_cast<double>(N)) * acc);
}

int main(int argc, char *argv[]) {
    size_t N = static_cast<size_t>(atoi(argv[1]));

    if (N > MAX_N) {
        std::cout << "Greater than max" << std::endl;
        exit(1);
    }

    int nums[N];

    for (int i = 0; i < N; i++) {
        nums[i] = get_rand(RAND_RANGE);
    }

    std::cout << "The randomly generated array is: " << std::endl;
    for (auto i : nums)
        std::cout << i << std::endl;

    double current_mean = mean(nums, N);
    std::cout << "The mean of the set is: " << current_mean << std::endl;

    double current_std_dev = std_dev(current_mean, nums, N);
    std::cout << "The standard deviation of the set is: " << current_std_dev << std::endl;

    return 0;
}
