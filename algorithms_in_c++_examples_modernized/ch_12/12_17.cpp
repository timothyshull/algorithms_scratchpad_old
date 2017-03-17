private:

link joinR(link a, link b)
{
    if (b == 0) { return a; }
    if (a == 0) { return b; }
    insertT(b, a->item);
    b->l = joinR(a->l, b->l);
    b->r = joinR(a->r, b->r);
    delete a;
    return b;
}

public:

void join(ST <Item, Key>& b) { head = joinR(head, b.head); }


