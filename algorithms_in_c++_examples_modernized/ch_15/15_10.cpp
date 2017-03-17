struct Node {
    Item item;
    int d;
    Node* l, * m, * r;

    Node(Item x, int k)
    {
        item = x;
        d = k;
        l = 0;
        m = 0;
        r = 0;
    }

    Node(Node* h, int k)
    {
        d = k;
        l = 0;
        m = h;
        r = 0;
    }

    int internal() { return d != NULLdigit; }
};

using Link = Node*;

Link heads[R];

Item nullItem;

