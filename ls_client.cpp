#include <iostream>
#include "linked_stack.h"

int main() {
    linked_stack<string> s{};
    while (std::cin.good()) {
        string item;
        std::getline(std::cin, item);
        if (item != "-")
            s.push(item);
        else if (!s.is_empty())
            std::cout << s.pop() << " ";
        std::cout << "(" << s.size() << " left on stack)";
    }
}