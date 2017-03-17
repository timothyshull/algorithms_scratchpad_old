struct Node {
    Item item;
    Node* next;

    Node(Item x)
    {
        item = x;
        next = 0;
    }
};

using Link = Node*;

Link randlist(int);

Link scanlist(int&);

void showlist(Link);

Link sortlist(Link);

