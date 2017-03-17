private:

link split(link p, link q, int d)
{
    link t = new node(nullItem);
    t->max_size = 2;
    Key v = p->item.key();
    Key w = q->item.key();
    switch (digit(v, d) * 2 + digit(w, d)) {
        case 0:
            t->l = split(p, q, d + 1);
            break;
        case 1:
            t->l = p;
            t->r = q;
            break;
        case 2:
            t->r = p;
            t->l = q;
            break;
        case 3:
            t->r = split(p, q, d + 1);
            break;
    }
    return t;
}

void insertR(link& h, Item x, int d)
{
    if (h == 0) {
        h = new node(x);
        return;
    }
    if (h->l == 0 && h->r == 0) {
        h = split(new node(x), h, d);
        return;
    }
    if (digit(x.key(), d) == 0) {
        insertR(h->l, x, d + 1);
    } else { insertR(h->r, x, d + 1); }
}

public:

ST(int maxN) { head = 0; }

void insert(Item item) { insertR(head, item, 0); }

