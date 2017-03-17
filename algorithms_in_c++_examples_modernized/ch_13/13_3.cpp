private:

link joinR(link a, link b)
{
    if (a == 0) { return b; }
    if (b == 0) { return a; }
    insertR(b, a->item);
    b->l = joinR(a->l, b->l);
    b->r = joinR(a->r, b->r);
    delete a;
    fixN(b);
    return b;
}

public:

void join(ST <Item, Key>& b)
{
    int N = head->N;
    if (rand() / (RAND_MAX / (N + b.head->N) + 1) < N) {
        head = joinR(head, b.head);
    } else { head = joinR(b.head, head); }
}

