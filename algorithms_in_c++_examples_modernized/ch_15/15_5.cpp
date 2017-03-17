private:

link insertR(link h, Item x, int d, link p)
{
    Key v = x.key();
    if ((h->bit >= d) || (h->bit <= p->bit)) {
        link t = new node(x);
        t->bit = d;
        t->l = (digit(v, t->bit) ? h : t);
        t->r = (digit(v, t->bit) ? t : h);
        return t;
    }
    if (digit(v, h->bit) == 0) {
        h->l = insertR(h->l, x, d, h);
    } else { h->r = insertR(h->r, x, d, h); }
    return h;
}

public:

void insert(Item x)
{
    Key v = x.key();
    int i;
    Key w = searchR(head->l, v, -1).key();
    if (v == w) { return; }
    for (i = 0; digit(v, i) == digit(w, i); ++i) {}
    head->l = insertR(head->l, x, i, head);
}

ST(int maxN)
{
    head = new node(nullItem);
    head->l = head->r = head;
}

