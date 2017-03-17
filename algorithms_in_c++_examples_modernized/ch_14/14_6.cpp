void insert(Item item)
{
    Key v = item.key();
    int i = hash(v, M), k = hashtwo(v, M);
    while (!st[i].null()) { i = (i + k) % M; }
    st[i] = item;
    ++N;
}

Item search(Key v)
{
    int i = hash(v, M), k = hashtwo(v, M);
    while (!st[i].null()) {
        if (v == st[i].key()) { return st[i]; }
        else { i = (i + k) % M; }
    }
    return nullItem;
}

