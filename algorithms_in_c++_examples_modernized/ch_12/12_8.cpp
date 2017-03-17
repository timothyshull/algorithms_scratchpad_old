template<class Item, class Key>
class ST {
private:
    struct node {
        Item item;
        node* l, * r;

        node(Item x)
        {
            item = x;
            l = 0;
            r = 0;
        }
    };

    using link = node*;
    link head;
    Item nullItem;

    Item searchR(link h, Key v)
    {
        if (h == 0) { return nullItem; }
        Key t = h->item.key();
        if (v == t) { return h->item; }
        if (v < t) { return searchR(h->l, v); }
        else { return searchR(h->r, v); }
    }

    void insertR(link& h, Item x)
    {
        if (h == 0) {
            h = new node(x);
            return;
        }
        if (x.key() < h->item.key()) {
            insertR(h->l, x);
        } else { insertR(h->r, x); }
    }

public:
    ST(int maxN) { head = 0; }

    Item search(Key v) { return searchR(head, v); }

    void insert(Item x) { insertR(head, x); }
};

