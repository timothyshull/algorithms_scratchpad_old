private:

void insertR(link& h, Item x)
{
    if (h == 0) {
        h = new node(x);
        return;
    }
    if (rand() < RAND_MAX / (h->max_size + 1)) {
        insertT(h, x);
        return;
    }
    if (x.key() < h->item.key()) {
        insertR(h->l, x);
    } else { insertR(h->r, x); }
    ++h->max_size;
}

public:

void insert(Item x) { insertR(head, x); }

