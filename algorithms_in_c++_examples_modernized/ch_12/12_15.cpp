void partR(link& h, int k)
{
    int t = (h->l == 0) ? 0 : h->l->N;
    if (t > k) {
        partR(h->l, k);
        rotR(h);
    }
    if (t < k) {
        partR(h->r, k - t - 1);
        rotL(h);
    }
}

