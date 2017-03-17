char* a;

int i;

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

Link parse()
{
    char t = ++a[i];
    Link x = new Node(t);
    if ((t == '+') || (t == '*')) {
        x->l = parse();
        x->r = parse();
    }
    return x;
}

