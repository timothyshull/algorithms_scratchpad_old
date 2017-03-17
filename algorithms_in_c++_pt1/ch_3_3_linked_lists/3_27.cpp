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

typedef node *link;

int main(int argc, char *argv[]) {
//    int i, N = atoi(argv[1]), M = atoi(argv[2]);
    int i;
    int N = 10;
    int M = 5;
    link t = new node(1, nullptr);
    t->next = t;
    for (i = 2; i <= N; i++) {
        t->next = new node(i, t->next);
        t = t->next;
    }
    while (t != t->next) {
        for (i = 1; i < M; i++) {
            t = t->next;
            t->next = t->next->next;
        }
        std::cout << t->item << "\n";
    }
    return 0;
}
