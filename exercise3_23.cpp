using Item = int;

struct node {
    Item item;
    node *next;

    node(Item x, node *t) : item{x}, next{t} {}
};

using link = node *;

int circular_list_length(link start) {
    int count = 1;

    link x = start;
    while (x->next != start) {
        x = x->next;
        count += 1;
    }

    return count;
}
