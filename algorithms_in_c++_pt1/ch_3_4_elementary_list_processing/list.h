#ifndef CH_3_4_ELEMENTARY_LIST_PROCESSING_LIST_H
#define CH_3_4_ELEMENTARY_LIST_PROCESSING_LIST_H

typedef int Item;

struct node {
    Item item;
    node *next;

    node(int x, node *t) {
        item = x;
        next = t;
    }
};

typedef node *link;
typedef link Node;

void construct(int);

Node newNode(int);

void deleteNode(Node);

void insert(Node, Node);

Node remove(Node);

Node next(Node);

Item item(Node);

#endif //CH_3_4_ELEMENTARY_LIST_PROCESSING_LIST_H
