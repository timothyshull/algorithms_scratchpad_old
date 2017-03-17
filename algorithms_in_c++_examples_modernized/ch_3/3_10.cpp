#include "list.h"

template<typename Item_type>
Link<Item_type> reverse(Link<Item_type> x)
{
    Link<Item_type> t;
    Link<Item_type> y{x};
    Link<Item_type> r{nullptr};
    while (y != nullptr) {
        t = y->next;
        y->next = r;
        r = y;
        y = t;
    }
    return r;
}

