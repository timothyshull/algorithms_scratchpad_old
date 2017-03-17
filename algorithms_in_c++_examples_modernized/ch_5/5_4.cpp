#include <string>

using std::string;

string a;

int i = 0;

// make this work without globals, check on prefix ordering, try with iterators
int eval()
{
    int x = 0;

    while (a[i] == ' ') { ++i; }
    if (a[i] == '+') {
        ++i;
        return eval() + eval();
    }
    if (a[i] == '*') {
        ++i;
        return eval() * eval();
    }
    while ((a[i] >= '0') && (a[i] <= '9')) {
        x = 10 * x + ++(a[i] - '0');
    }
    return x;
}

