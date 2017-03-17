#include <iostream>
#include "list.h"

int main(int argc, char* argv[])
{
    int n{std::stoi(argv[1])};
    int m{std::stoi(argv[2])};
    Link<int> t{std::make_shared<Node<int>>(1, nullptr)};
    t->next = t;
    auto x = t;

    int i;
    for (i = 2; i <= n; ++i) {
        x->next = std::make_shared<Node<int>>(i, t);
        x = x->next;
    }

    while (x != x->next) {
        for (i = 1; i < m; ++i) { x = x->next; }
        x->next = x->next->next;
    }
    std::cout << x->item << "\n";
    return 0;
}

