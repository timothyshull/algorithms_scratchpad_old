#include <iostream>
#include <cstdlib>

struct node {
    int item;
    node *next;

    node(int x, node *t) {
        item = x;
        next = t;
    }
};

int node_distance(node *x, node *t) {
    if (x == t || x == nullptr || t == nullptr) {
        return 0;
    }
    int count = 1;
    node *visitor = x;
    while (t != (visitor = visitor->next)) {
        count++;
    }
    return count;
}

node *build_clist(unsigned int size) {
    if (size == 0) {
        return nullptr;
    }
    node *t = new node(1, nullptr);
    t->next = t;
    if (size == 1) {
        return t;
    }
    node *x = t;
    for (int i = 2; i <= size; i++) {
        x = (x->next = new node(i, t));
    }
    return t;
}

void free_list(node *head) {
    if (head == nullptr) {
        return;
    }
    if (head->next == head) {
        delete head;
        return;
    }
    node *x = head;
    do {
        node *tmp = x->next;
        delete x;
        x = tmp;
    } while (x != head);
}

node *get_node_at_distance(node *start, unsigned int distance) {
    if (distance == 0) {
        return start;
    }
    node *tmp = start->next;
    while (--distance > 0 && tmp != start) {
        tmp = tmp->next;
    }
//    for (; distance > 0; distance--) {
//        tmp = tmp->next;
//        distance--;
//        if (tmp == start) {
//            break;
//        }
//    }
    if (distance != 0) {
        return nullptr;
    } else {
        return tmp;
    }
}

int main(int argc, char *argv[]) {
    unsigned int distances[]{0, 1, 5, 10, 30, 75, 300};

    node *one_node = build_clist(1);
    std::cout << "The distance for a single-element circular list is: " << node_distance(one_node, one_node) << "\n";
    std::cout << "Test 1 with nullptr: " << node_distance(one_node, nullptr) << "\n";
    std::cout << "Test 1 with nullptr: " << node_distance(nullptr, one_node) << "\n";
    free_list(one_node);
    node *large_list = build_clist(600);
    for (auto i : distances) {
        node *dest = get_node_at_distance(large_list, i);
        std::cout << "The distance between the given nodes is " << node_distance(large_list, dest) << "\n";
    }
    free_list(large_list);
    return 0;
}