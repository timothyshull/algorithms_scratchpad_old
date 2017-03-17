#include "PQ.cxx"

template<class Item>
void PQsort(Item a[], int l, int r)
{
    int k;
    PQ <Item> pq(r - l + 1);
    for (k = l; k <= r; ++k) { pq.insert(a[k]); }
    for (k = r; k >= l; k--) { a[k] = pq.getmax(); }
}

