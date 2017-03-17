private:

void split(link h)
{
    link t = new node;
    while (h->m == 0 || h->m == M) {
        h->m = t->m = 0;
        for (int j = 0; j < M; ++j) {
            if (bits(h->b[j].key(), h->k, 1) == 0) {
                ++h->b[h->m] = h->b[j];
            } else { ++t->b[t->m] = h->b[j]; }
        }
        t->k = ++(h->k);
    }
    insertDIR(t, t->k);
}

void insert(link h, Item x)
{
    int j;
    Key v = x.key();
    for (j = 0; j < h->m; ++j) {
        if (v < h->b[j].key()) { break; }
    }
    for (int i = ++(h->m); i > j; i--) {
        h->b[i] = h->b[i - 1];
    }
    h->b[j] = x;
    if (h->m == M) { split(h); }
}

public:

void insert(Item x) { insert(dir[bits(x.key(), 0, d)], x); }

