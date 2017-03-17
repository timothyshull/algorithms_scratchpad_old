void remove(Item x)
{
    int i = hash(x.key(), M), j;
    while (!st[i].null()) {
        if (x.key() == st[i].key()) { break; }
        else { i = (i + 1) % M; }
    }
    if (st[i].null()) { return; }
    st[i] = nullItem;
    N--;
    for (j = i + 1; !st[j].null(); j = (j + 1) % M, N--) {
        Item v = st[j];
        st[j] = nullItem;
        insert(v);
    }
}

