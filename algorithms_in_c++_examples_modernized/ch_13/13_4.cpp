link joinLR(link a, link b)
{
    if (a == 0) { return b; }
    if (b == 0) { return a; }
    if (rand() / (RAND_MAX / (a->max_size + b->max_size) + 1) < a->max_size) {
        a->r = joinLR(a->r, b);
        return a;
    } else {
        b->l = joinLR(a, b->l);
        return b;
    }
}

