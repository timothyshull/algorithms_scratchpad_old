void traverse(link h, void visit(link))
{
    STACK <link> s(max);
    s.push(h);
    while (!s.empty()) {
        visit(h = s.pop());
        if (h->r != 0) { s.push(h->r); }
        if (h->l != 0) { s.push(h->l); }
    }
}

