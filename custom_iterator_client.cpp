//
// Created by Timothy Shull on 2/7/16.
//

#include "custom_iterator.h"

int main() {
    fixed_array<double> point3d(3);
    point3d[0] = 2.3;
    point3d[1] = 3.2;
    point3d[2] = 4.2;

    for (fixed_array<double>::iterator i = point3d.begin(); i != point3d.end(); i++) {
        std::cout << *i << " ";
    }

    std::cout << std::endl;

    std::vector<double> vec;
    std::copy(point3d.begin(), point3d.end(), std::back_inserter(vec));

    for (std::vector<double>::iterator i = vec.begin(); i != vec.end(); i++) {
        std::cout << *i << " ";
    }

    std::cout << std::endl;
    return 0;
}