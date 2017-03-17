private:

Item search(link h, Key v)
{
    for (int j = 0; j < h->m; ++j) {
        if (v == h->b[j].key()) { return h->b[j]; }
    }
    return nullItem;
}

public:

Item search(Key v) { return search(dir[bits(v, 0, d)], v); }

