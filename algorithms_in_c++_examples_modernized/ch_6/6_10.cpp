#include <iostream>
#include <cstdlib>
#include "Item.h"

using std::cin;
using std::cout;

int operator<(const Item& A, const Item& B) { return A.key < B.key; }

int scan(Item& x) { return (std::cin >> x.key >> x.info) != 0; }

void rand(Item& x)
{
    x.key = 1000 * (1.0 * rand() / RAND_MAX);
    x.info = 1.0 * rand() / RAND_MAX;
}

void show(const Item& x) { std::cout << x.key << " " << x.info << endl; }

