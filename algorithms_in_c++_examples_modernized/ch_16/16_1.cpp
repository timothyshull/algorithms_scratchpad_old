template<class Item, class Key>
struct entry { Key key; Item item; struct Node* next; };

struct Node {
    int m;
    entry<Item, Key> b[M];

    Node() { m = 0; }
};

using Link = Node*;

