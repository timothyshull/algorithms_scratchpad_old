#include <cstdlib>
#include <memory>
#include <random>
#include "list.h"

void list_insertion_sort(std::size_t n)
{
    Node<int> head_a{0, nullptr};
    Raw_node_pointer<int> a{&head_a};
    Raw_node_pointer<int> t{a};

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<int> uniform_dist(0, 999);

    for (int i = 0; i < n; ++i) {
        t->next = std::make_shared(uniform_dist(gen), nullptr);
        t = t->next.get();
    }

    Node<int> head_b{0, nullptr};
    Raw_node_pointer<int> u;
    Raw_node_pointer<int> x;
    Raw_node_pointer<int> b{&head_b};

    for (t = a->next.get(); t != nullptr; t = u) {
        u = t->next.get();
        for (x = b; x->next != nullptr; x = x->next.get()) {
            if (x->next->item > t->item) { break; }
        }
        t->next = x->next;
        x->next = t;
    }
}