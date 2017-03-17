private:

void insertT(link& h, Item x)
{
    if (h == 0) {
        h = new node(x);
        return;
    }
    if (x.key() < h->item.key()) {
        insertT(h->l, x);
        rotR(h);
    } else {
        insertT(h->r, x);
        rotL(h);
    }
}

public:

void insert(Item item) { insertT(head, item); }

