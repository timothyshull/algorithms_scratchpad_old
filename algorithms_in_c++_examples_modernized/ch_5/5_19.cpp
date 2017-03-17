struct Node {
    Item item;
    Node* l, * r;

    Node(Item x)
    {
        item = x;
        l = 0;
        r = 0;
    }
};

using Link = Node*;

Link max(Item a[], int l, int r)
{
    int m = (l + r) / 2;
    Link x = new Node(a[m]);
    if (l == r) { return x; }
    x->l = max(a, l, m);
    x->r = max(a, m + 1, r);
    Item u = x->l->item, v = x->r->item;
    if (u > v) {
        x->item = u;
    } else { x->item = v; }
    return x;
}

