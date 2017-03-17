#include <climits>
#include <iostream>
#include <cfloat>

int main() {
    std::cout << "'int' min: " << INT_MIN << std::endl;
    std::cout << "'int' max: " << INT_MAX << std::endl;
    std::cout << "'long' min: " << LONG_MIN << std::endl;
    std::cout << "'long' max: " << LONG_MAX << std::endl;
    std::cout << "'short' min: " << SHRT_MIN << std::endl;
    std::cout << "'short' max: " << SHRT_MAX << std::endl;
    std::cout << "'float' min: " << FLT_MIN << std::endl;
    std::cout << "'float' max: " << FLT_MAX << std::endl;
    std::cout << "'double' min: " << DBL_MIN << std::endl;
    std::cout << "'double' max: " << DBL_MAX << std::endl;
    return 0;
}