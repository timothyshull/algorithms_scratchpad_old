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


void build_clist_and_count(unsigned int size) {
    std::cout << "The input size is: " << size << "\n";
    node *list = build_clist(size);
    std::cout << "The calculated size is: " << num_nodes_in_clist(list) << "\n";
    free_list(list);
}

int main(int argc, char *argv[]) {
    unsigned int sizes[]{0, 1, 5, 10, 30, 75, 300};

    for (auto i : sizes) {
        build_clist_and_count(i);
    }
    return 0;
}