#include <cstdlib>
#include <iostream>
#include "Item.h"
#include "exch.h"
#include "Array.h"

using std::cin;
using std::cout;

int main(int argc, char* argv[])
{
    int N = atoi(argv[1]), sw = atoi(argv[2]);
    Item* a = new Item[N];
    if (sw) { rand(a, N); } else { scan(a, N); }
    sort(a, 0, N - 1);
    show(a, 0, N - 1);
    return 0;
}
