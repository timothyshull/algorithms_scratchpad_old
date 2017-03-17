#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Item.h"

using std::cin;
using std::cout;

static char buf[100000];

static int cnt = 0;

int operator<(const Item& a, const Item& b) { return strcmp(a.str, b.str) < 0; }

void show(const Item& x) { std::cout << x.str << " "; }

int scan(Item& x)
{
    int flag = (std::cin >> (x.str = &buf[cnt])) != 0;
    cnt += strlen(x.str) + 1;
    return flag;
}

