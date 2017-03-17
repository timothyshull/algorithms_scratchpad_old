#include <iostream>
#include <string>
#include "Stack.h"

using std::cout;
using std::string;

int main(int argc, char* argv[])
{
    string a{argv[1]};
    int n{a.size()};
    Stack<char> ops{n};
    for (int i = 0; i < n; ++i) {
        if (a[i] == ')') {
            std::cout << ops.pop() << " ";
        }
        if ((a[i] == '+') || (a[i] == '*')) {
            ops.push(a[i]);
        }
        if ((a[i] >= '0') && (a[i] <= '9')) {
            std::cout << a[i] << " ";
        }
    }
    std::cout << "\n";
    return 0;
}

