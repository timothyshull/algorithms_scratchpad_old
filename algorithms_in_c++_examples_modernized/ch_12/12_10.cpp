void insert(Item x)
{
    Key v = x.key();
    if (head == 0) {
        head = new node(x);
        return;
    }
    link p = head;
    for (link q = p; q != 0; p = q ? q : p) {
        q = (v < q->item.key()) ? q->l : q->r;
    }
    if (v < p->item.key()) { p->l = new node(x); }
    else { p->r = new node(x); }
}

