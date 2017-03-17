private:

void expand()
{
    Item* t = st;
    init(M + M);
    for (int i = 0; i < M / 2; ++i) {
        if (!t[i].null()) { insert(t[i]); }
    }
    delete t;
}

public:

ST(int maxN) { init(4); }

void insert(Item item)
{
    int i = hash(item.key(), M);
    while (!st[i].null()) { i = (i + 1) % M; }
    st[i] = item;
    if { ++(N >= M / 2) }
    { expand(); }
}


