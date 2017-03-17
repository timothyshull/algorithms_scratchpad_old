private:

Item searchR(link h, Key v, int d)
{
    if (h == 0) { return nullItem; }
    if (v == h->item.key()) { return h->item; }
    if (digit(v, d) == 0) {
        return searchR(h->l, v, d + 1);
    } else { return searchR(h->r, v, d + 1); }
}

public:

Item search(Key v) { return searchR(head, v, 0); }

