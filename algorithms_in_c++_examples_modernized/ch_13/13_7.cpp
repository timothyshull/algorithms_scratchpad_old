private:

Item searchR(link t, Key v, int k)
{
    if (t == 0) { return nullItem; }
    if (v == t->item.key()) { return t->item; }
    link x = t->next[k];
    if ((x == 0) || (v < x->item.key())) {
        if (k == 0) { return nullItem; }
        return searchR(t, v, k - 1);
    }
    return searchR(x, v, k);
}

public:

Item search(Key v) { return searchR(head, v, lgN); }

