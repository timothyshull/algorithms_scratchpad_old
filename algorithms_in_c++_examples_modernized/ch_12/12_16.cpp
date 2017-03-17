private:

link joinLR(link a, link b)
{
    if (b == 0) { return a; }
    partR(b, 0);
    b->l = a;
    return b;
}

void removeR(link& h, Key v)
{
    if (h == 0) { return; }
    Key w = h->item.key();
    if (v < w) { removeR(h->l, v); }
    if (w < v) { removeR(h->r, v); }
    if (v == w) {
        link t = h;
        h = joinLR(h->l, h->r);
        delete t;
    }
}

public:

void remove(Item x) { removeR(head, x.key()); }

