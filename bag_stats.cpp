#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

#include "Linked_bag.h"

int main() {
    Linked_bag<double> numbers;

    for (std::string line; std::getline(std::cin, line);) {
        if (line == "") {
            break;
        } else {
            double tmp = atof(line.c_str());
            numbers.add(tmp);
        }

        int n = static_cast<int>(numbers.size());
        double sum = 0.0;
        for (auto x : numbers) {
            sum += x;
        }
        double mean = sum / n;
        sum = 0.0;
        for (auto x : numbers) {
            sum += (x - mean) * (x - mean);
        }
        double std_dev = sqrt(sum / (n - 1));

        std::stringstream ss;
        ss << "Mean: " << std::setprecision(2) << mean << "\n";
        ss << "Std deviation: " << std::setprecision(2) << std_dev << "\n";
        std::cout << ss.str();
    }

    return 0;
}
