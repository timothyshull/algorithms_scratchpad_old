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

void join_circular_lists(node *x, node *t) {
    if (x == nullptr || t == nullptr) {
        return;
    }
    node *tmp = x->next;
    x->next = t->next;
    t->next = tmp;
}

int num_nodes_in_clist(node *start) {
    if (start == nullptr) {
        return 0;
    }
    if (start->next == start) {
        return 1;
    }
    int count = 0;
    node *visitor = start;
    do {
        count++;
        visitor = visitor->next;
    } while (visitor != start);
    return count;
}

int main() {
    node *list1 = build_clist(5);
    node *list2 = build_clist(6);
    join_circular_lists(list1, list2);
    std::cout << "The size of list1 is: " << num_nodes_in_clist(list1) << "\n";
    std::cout << "The size of list2 is: " << num_nodes_in_clist(list2) << "\n";
    return 0;
}