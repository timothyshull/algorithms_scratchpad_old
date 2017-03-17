void balanceR(link& h)
{
    if ((h == 0) || (h->max_size == 1)) { return; }
    partR(h, h->max_size / 2);
    balanceR(h->l);
    balanceR(h->r);
}

