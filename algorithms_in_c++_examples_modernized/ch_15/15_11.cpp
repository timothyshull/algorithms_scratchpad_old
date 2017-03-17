private:

link split(link p, link q, int d)
{
    int pd = digit(p->item.key(), d),
            qd = digit(q->item.key(), d);
    link t = new node(nullItem, qd);
    if (pd < qd) {
        t->m = q;
        t->l = new node(p, pd);
    }
    if (pd == qd) { t->m = split(p, q, d + 1); }
    if (pd > qd) {
        t->m = q;
        t->r = new node(p, pd);
    }
    return t;
}

link newext(Item x) { return new node(x, NULLdigit); }

void insertR(link& h, Item x, int d)
{
    int i = digit(x.key(), d);
    if (h == 0) {
        h = new node(newext(x), i);
        return;
    }
    if (!h->internal()) {
        h = split(newext(x), h, d);
        return;
    }
    if (i < h->d) { insertR(h->l, x, d); }
    if (i == h->d) { insertR(h->m, x, d + 1); }
    if (i > h->d) { insertR(h->r, x, d); }
}

public:

ST(int maxN) { for (int i = 0; i < R; ++i) { heads[i] = 0; }}

void insert(Item x) { insertR(heads[digit(x.key(), 0)], x, 1); }

