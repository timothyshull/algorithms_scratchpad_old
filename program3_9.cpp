#include <iostream>

using Item = int;

struct node {
    Item item;
    node *next;

    node(Item x, node *t) : item{x}, next{t} {}

};

using link = node *;

int main(int argc, char *argv[]) {
    int i;
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);

    link t = new node{1, 0};
    t->next = t;
    link x = t;
    for (i = 2; i <= N; i++)
        x = (x->next = new node{i, t});
    while (x != x->next) {
        for (i = 1; i < M; i++)
            x = x->next;
    }
    std::cout << x->item << std::endl;

    return 0;
}
