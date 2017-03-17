private:

struct Node {
    Item item;
    Node** next;
    int sz;

    Node(Item x, int k)
    {
        item = x;
        sz = k;
        next = new Node* [k];
        for (int i = 0; i < k; ++i) { next[i] = 0; }
    }
};

using Link = Node*;

Link head;

Item nullItem;

int lgN;

public:

ST(int)
{
    head = new Node(nullItem, lgNmax);
    lgN = 0;
}

