private:

Item searchR(link h, Key v, int d)
{
    if (h->bit <= d) { return h->item; }
    if (digit(v, h->bit) == 0) {
        return searchR(h->l, v, h->bit);
    } else { return searchR(h->r, v, h->bit); }
}

public:

Item search(Key v)
{
    Item t = searchR(head, v, -1);
    return (v == t.key()) ? t : nullItem;
}

