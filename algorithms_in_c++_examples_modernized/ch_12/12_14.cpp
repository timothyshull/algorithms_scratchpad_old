private:

Item selectR(link h, int k)
{
    if (h == 0) { return nullItem; }
    int t = (h->l == 0) ? 0 : h->l->N;
    if (t > k) { return selectR(h->l, k); }
    if (t < k) { return selectR(h->r, k - t - 1); }
    return h->item;
}

public:

Item select(int k) { return selectR(head, k); }

