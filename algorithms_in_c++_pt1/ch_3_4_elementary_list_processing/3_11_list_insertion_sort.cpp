#include <iostream>
#include <cstdlib>
#include "list.h"

static const int N = 10;

int main() {
    node heada(0, nullptr);
    link a = &heada, t = a;
    for (int i = 0; i < N; i++) {
        t = (t->next = new node(rand() % 1000, nullptr));
    }
    node headb(0, nullptr);
    link u, x, b = &headb;
    for (t = a->next; t != nullptr; t = u) {
        u = t->next;
        for (x = b; x->next != nullptr; x = x->next) {
            if (x->next->item > t->item) {
                break;
            }
        }
        t->next = x->next;
        x->next = t;
    }
    return 0;
}

// set t to head of list
