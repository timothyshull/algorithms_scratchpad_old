#include <iostream>

struct node {
    int item;
    node *next;

    node(int x, node *t) : item{x}, next{t} { }
};

using link = node *;

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);

    // One element circular linked list
    link t = new node{1, nullptr};
    t->next = t;
    link x{t};

    int i;
    for (i = 2; i <= N; i++) {
        x->next = new node{i, t};
        x = x->next;
//        x = (x->next = new node{i, t});
    }
    int counter{0};
    while (x != x->next) {
        for (i = 1; i < M; i++) {
            x = x->next;
            counter += 1;
        }
        x->next = x->next->next;
    }
    std::cout << x->item << std::endl;
    std::cout << counter << std::endl;
}
