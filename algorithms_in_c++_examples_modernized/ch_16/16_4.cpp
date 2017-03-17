link split(link h)
{
    link t = new node();
    for (int j = 0; j < M / 2; ++j) {
        t->b[j] = h->b[M / 2 + j];
    }
    h->m = M / 2;
    t->m = M / 2;
    return t;
}

