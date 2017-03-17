static link pair(link p, link q)
{
    if (p->item < q->item) {
        p->r = q->l;
        q->l = p;
        return q;
    } else {
        q->r = p->l;
        p->l = q;
        return p;
    }
}

