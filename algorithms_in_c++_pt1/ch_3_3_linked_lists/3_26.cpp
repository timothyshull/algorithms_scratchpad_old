struct node {
    int item;
    node *next;
};

void swap_successive_node(node *x, node *t) {
    if (x == nullptr || t == nullptr) {
        return;
    }
    node *tmp = t->next;
    t->next = tmp->next;
    tmp->next = x->next->next;
    x->next->next = tmp;
}