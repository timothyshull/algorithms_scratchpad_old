#include <iostream>
#include "bag.h"

using std::string;
using namespace algos2;

int main() {
    bag<string> str_bag;
    string tmp;
    while (getline(std::cin, tmp)) {
        str_bag.add(tmp);
    }

    std::cout << "The current size of the bag is: " << str_bag.size() << "\n";
//    for (auto s : str_bag) {
//        std::cout << s;
//    }

    for (bag<string>::iterator it = str_bag.begin(); it != str_bag.end(); it++) {
        std::cout << *it << "\n";
    }

    return 0;
}