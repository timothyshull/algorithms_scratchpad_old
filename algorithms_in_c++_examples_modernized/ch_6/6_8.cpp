#include <iostream>
#include <cstdlib>
#include "Array.h"

using std::cin;
using std::cout;

template<class Item>
void rand(Item a[], int N) { for (int i = 0; i < N; ++i) { rand(a[i]); }}

template<class Item>
void scan(Item a[], int& N)
{
    for (int i = 0; i < N; ++i) {
        if (!scan(a[i])) { break; }
    }
    N = i;
}

template<class Item>
void show(Item a[], int l, int r)
{
    for (int i = l; i <= r; ++i) {
        show(a[i]);
    }
    std::cout << endl;
}

