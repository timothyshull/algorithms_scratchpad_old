#include <iostream>
#include <cmath>

#include "Linked_stack.h"

int main() {
    Linked_stack<std::string> ops;
    Linked_stack<double> vals;
    for (std::string s; std::getline(std::cin, s) && s != "";) {
        if (s == "(") {
        } else if (s == "+" || s == "-" || s == "*" || s == "/" || s == "sqrt") {
            ops.push(s);
        } else if (s == ")") {
            std::string op = ops.pop();
            double v = vals.pop();

            if (op == "+") {
                v = vals.pop() + v;
            } else if (op == "-") {
                v = vals.pop() - v;
            } else if (op == "*") {
                v = vals.pop() * v;
            } else if (op == "/") {
                v = vals.pop() / v;
            } else if (op == "sqrt") {
                v = std::sqrt(v);
            }
            vals.push(v);
        } else {
            double v = std::atof(s.c_str());
            vals.push(v);
        }
    }
    std::cout << vals.pop() << "\n";
    return 0;
}
