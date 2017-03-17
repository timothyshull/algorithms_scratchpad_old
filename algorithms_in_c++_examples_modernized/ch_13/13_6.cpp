private:

int red(link x)
{
    if (x == 0) { return 0; }
    return x->red;
}

void RBinsert(link& h, Item x, int sw)
{
    if (h == 0) {
        h = new node(x);
        return;
    }
    if (red(h->l) && red(h->r)) {
        h->red = 1;
        h->l->red = 0;
        h->r->red = 0;
    }
    if (x.key() < h->item.key()) {
        RBinsert(h->l, x, 0);
        if (red(h) && red(h->l) && sw) { rotR(h); }
        if (red(h->l) && red(h->l->l)) {
            rotR(h);
            h->red = 0;
            h->r->red = 1;
        }
    } else {
        RBinsert(h->r, x, 1);
        if (red(h) && red(h->r) && !sw) { rotL(h); }
        if (red(h->r) && red(h->r->r)) {
            rotL(h);
            h->red = 0;
            h->l->red = 1;
        }
    }
}

public:

void insert(Item x)
{
    RBinsert(head, x, 0);
    head->red = 0;
}

