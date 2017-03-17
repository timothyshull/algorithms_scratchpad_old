void rotR(link& h)
{
    link x = h->l;
    h->l = x->r;
    x->r = h;
    h = x;
}

void rotL(link& h)
{
    link x = h->r;
    h->r = x->l;
    x->l = h;
    h = x;
}

