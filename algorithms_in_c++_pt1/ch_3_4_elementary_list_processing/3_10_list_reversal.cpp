#include <iostream>
#include <cstdlib>

#include "list.h"

link reverse(link x) {
    link t;
    link y = x;
    link r = 0;

    while (y != nullptr) {
        t = y->next;
        y->next = r;
        r = y;
        y = t;
    }
    return r;
}
