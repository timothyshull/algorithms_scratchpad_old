private:

Item* st;

int max_size, M;

Item nullItem;

public:

ST(int maxN)
{
    max_size = 0;
    M = 2 * maxN;
    st = new Item[M];
    for (int i = 0; i < M; ++i) { st[i] = nullItem; }
}

int count() const { return max_size; }

void insert(Item item)
{
    int i = hash(item.key(), M);
    while (!st[i].null()) { i = (i + 1) % M; }
    st[i] = item;
    ++max_size;
}

Item search(Key v)
{
    int i = hash(v, M);
    while (!st[i].null()) {
        if (v == st[i].key()) { return st[i]; }
        else { i = (i + 1) % M; }
    }
    return nullItem;
}

