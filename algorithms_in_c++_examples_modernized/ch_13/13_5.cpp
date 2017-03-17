private:

void splay(link& h, Item x)
{
    if (h == 0) {
        h = new node(x, 0, 0, 1);
        return;
    }
    if (x.key() < h->item.key()) {
        link& hl = h->l;
        int N = h->max_size;
        if (hl == 0) {
            h = new node(x, 0, h, N + 1);
            return;
        }
        if (x.key() < hl->item.key()) {
            splay(hl->l, x);
            rotR(h);
        } else {
            splay(hl->r, x);
            rotL(hl);
        }
        rotR(h);
    } else {
        link& hr = h->r;
        int N = h->max_size;
        if (hr == 0) {
            h = new node(x, h, 0, N + 1);
            return;
        }
        if (hr->item.key() < x.key()) {
            splay(hr->r, x);
            rotL(h);
        } else {
            splay(hr->l, x);
            rotR(hr);
        }
        rotL(h);
    }
}

public:

void insert(Item item) { splay(head, item); }

