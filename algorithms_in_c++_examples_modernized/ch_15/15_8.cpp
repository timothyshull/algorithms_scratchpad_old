private:

struct Node {
    Item item;
    int d;
    Node* l, * m, * r;

    Node(int k)
    {
        d = k;
        l = 0;
        m = 0;
        r = 0;
    }
};

using Link = Node*;

Link head;

Item nullItem;

Item searchR(Link h, Key v, int d)
{
    int i = digit(v, d);
    if (h == 0) { return nullItem; }
    if (i == NULLdigit) {
        Item dummy(v);
        return dummy;
    }
    if (i < h->d) { return searchR(h->l, v, d); }
    if (i == h->d) { return searchR(h->m, v, d + 1); }
    if (i > h->d) { return searchR(h->r, v, d); }
}

void insertR(Link& h, Item x, int d)
{
    int i = digit(x.key(), d);
    if (h == 0) { h = new Node(i); }
    if (i == NULLdigit) { return; }
    if (i < h->d) { insertR(h->l, x, d); }
    if (i == h->d) { insertR(h->m, x, d + 1); }
    if (i > h->d) { insertR(h->r, x, d); }
}

public:

ST(int maxN) { head = 0; }

Item search(Key v) { return searchR(head, v, 0); }

void insert(Item x) { insertR(head, x, 0); }

