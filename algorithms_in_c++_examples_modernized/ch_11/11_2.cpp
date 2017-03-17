template<class Item>
void merge(Item a[], int l, int m, int r)
{
    if (r == l + 1) { compexch(a[l], a[r]); }
    if (r < l + 2) { return; }
    unshuffle(a, l, r);
    merge(a, l, (l + m) / 2, m);
    merge(a, m + 1, (m + 1 + r) / 2, r);
    shuffle(a, l, r);
    for (int i = l + 1; i < r; i += 2) {
        compexch(a[i], a[i + 1]);
    }
}

