private:

Item searchR(link h, Key v, int d)
{
    if (h == 0) { return nullItem; }
    if (h->internal()) {
        int i = digit(v, d), k = h->d;
        if (i < k) { return searchR(h->l, v, d); }
        if (i == k) { return searchR(h->m, v, d + 1); }
        if (i > k) { return searchR(h->r, v, d); }
    }
    if (v == h->item.key()) { return h->item; }
    return nullItem;
}

public:

Item search(Key v) { return searchR(heads[digit(v, 0)], v, 1); }

