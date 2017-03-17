#include <iostream>
#include <list>
#include <memory>

struct node {
    int data;
    node *next;

    node(int n, node *nptr) : data{n}, next{nptr} { }

    ~node() {
        next = nullptr;
    }
};

int num_nodes(node *head) {
    node *visitor{head};
    int counter{1};
    while (visitor->next != head) {
        visitor = visitor->next;
        counter += 1;
    }
    return counter;
}

int main() {
    node *t = new node{1, nullptr};
//    t->next = t; -> unnecessary here
    node *x{t};
    for (int i{2}; i <= 3; i++) {
        x->next = new node{i, t};
        x = x->next;
    }

    int node_count = num_nodes(t);
    std::cout << node_count << std::endl;

    x->next = nullptr;
    x = nullptr;
    while (t) {
        node *tmp{t};
        t = t->next;
        delete tmp;
    }
    std::cout << "here" << std::endl;
    return 0;
}
