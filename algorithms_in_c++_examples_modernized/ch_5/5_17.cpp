int count(link h)
{
    if (h == 0) { return 0; }
    return count(h->l) + count(h->r) + 1;
}

int height(link h)
{
    if (h == 0) { return -1; }
    int u = height(h->l), v = height(h->r);
    if (u > v) { return u + 1; } else { return v + 1; }
}

