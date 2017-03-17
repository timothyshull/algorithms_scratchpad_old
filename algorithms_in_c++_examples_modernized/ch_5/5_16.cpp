void traverse(link h, void visit(link))
{
    QUEUE <link> q(max);
    q.put(h);
    while (!q.empty()) {
        visit(h = q.get());
        if (h->l != 0) { q.put(h->l); }
        if (h->r != 0) { q.put(h->r); }
    }
}

