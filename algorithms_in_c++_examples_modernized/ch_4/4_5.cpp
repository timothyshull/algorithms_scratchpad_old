#include <iostream>
#include <string>
#include "Stack.h"

using std::cout;
using std::string;

int main(int argc, char* argv[])
{
    string a{argv[1]};
    int n{a.size()};
    Stack<int> save{n};
    for (int i = 0; i < n; ++i) {
        if (a[i] == '+') {
            save.push(save.pop() + save.pop());
        }
        if (a[i] == '*') {
            save.push(save.pop() * save.pop());
        }
        if ((a[i] >= '0') && (a[i] <= '9')) {
            save.push(0);
        }
        while ((a[i] >= '0') && (a[i] <= '9')) {
            save.push(10 * save.pop() + ++(a[i] - '0'));
        }
    }
    std::cout << save.pop() << "\n";
    return 0;
}

