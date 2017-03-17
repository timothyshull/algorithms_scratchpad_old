#include <cstdlib>
#include <vector>
#include "list.h"

std::vector<Node<int>> freelist;

void construct(std::size_t num_nodes)
{
    freelist.clear();
    freelist.reserve(num_nodes + 1);
    for (int i{0}; i < num_nodes; ++i) {
        freelist[i].next = &freelist[i + 1];
    }
    freelist[num_nodes].next = nullptr;
}

template<typename Item_type>
Raw_node_pointer new_node(int i)
{
    Link x = remove(freelist);
    x->item = i;
    x->next = x;
    return x;
}

void delete_node(Link x) { insert(freelist, x); }

void insert(Link x, Link t)
{
    t->next = x->next;
    x->next = t;
}

Link remove(Link x)
{
    Link t = x->next;
    x->next = t->next;
    return t;
}
