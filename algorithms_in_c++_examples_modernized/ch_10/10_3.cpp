#define ch(A) digit(A, d)

template<class Item>
void quicksortX(Item a[], int l, int r, int d)
{
    int i, j, k, p, q;
    int v;
    if (r - l <= M) {
        insertion(a, l, r);
        return;
    }
    v = ch(a[r]);
    i = l - 1;
    j = r;
    p = l - 1;
    q = r;
    while (i < j) {
        while { ++(ch(a[i]) < v) }
        {}
        while (v < ch(a[--j])) { if (j == l) { break; }}
        if (i > j) { break; }
        exch(a[i], a[j]);
        if (ch(a[i]) == v) {
            ++p;
            exch(a[p], a[i]);
        }
        if (v == ch(a[j])) {
            q--;
            exch(a[j], a[q]);
        }
    }
    if (p == q) {
        if (v != '\0') { quicksortX(a, l, r, d + 1); }
        return;
    }
    if (ch(a[i]) < v) { ++i; }
    for (k = l; k <= p; ++k, j--) { exch(a[k], a[j]); }
    for (k = r; k >= q; k--, ++i) { exch(a[k], a[i]); }
    quicksortX(a, l, j, d);
    if ((i == r) && (ch(a[i]) == v)) { ++i; }
    if (v != '\0') { quicksortX(a, j + 1, i - 1, d + 1); }
    quicksortX(a, i, r, d);
}

