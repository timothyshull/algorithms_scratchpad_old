private:

Item searchR(link h, Key v, int ht)
{
    int j;
    if (ht == 0) {
        for (j = 0; j < h->m; ++j) {
            if (v == h->b[j].key) {
                return h->b[j].item;
            }
        }
    } else {
        for (j = 0; j < h->m; ++j) {
            if ((j + 1 == h->m) || (v < h->b[j + 1].key)) {
                return searchR(h->b[j].next, v, ht - 1);
            }
        }
    }
    return nullItem;
}

public:

Item search(Key v) { return searchR(head, v, HT); }

