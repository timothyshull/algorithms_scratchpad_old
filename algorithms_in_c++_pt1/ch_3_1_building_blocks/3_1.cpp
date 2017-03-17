#include <iostream>
#include <limits>

int main() {
    std::cout << "int: min - " << std::numeric_limits<int>::lowest() << ", max - " << std::numeric_limits<int>::max() << '\n';
    std::cout << "long int: min - " << std::numeric_limits<long int>::lowest() << ", max - " << std::numeric_limits<long int>::max() << '\n';
    std::cout << "short int: min - " << std::numeric_limits<short int>::lowest() << ", max - " << std::numeric_limits<short int>::max() << '\n';
    std::cout << "float: min - " << std::numeric_limits<float>::lowest() << ", max - " << std::numeric_limits<float>::max() << '\n';
    std::cout << "double: min - " << std::numeric_limits<double>::lowest() << ", max - " << std::numeric_limits<double>::max() << '\n';
    return 0;
}
