using Item = void *;

struct node {
    Item item;
    node *next;

    node(Item x, node *t) : item{x}, next{t} {}

};
using link = node *;
