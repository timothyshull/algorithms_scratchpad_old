#ifndef CH_4_0_ABSTRACT_DATA_TYPES_LIST_H
#define CH_4_0_ABSTRACT_DATA_TYPES_LIST_H

// made generic then removed (not splitting to .h/.cpp)
class list {
    using Item = int;

    struct node {
        Item item;
        node *next;

        node(int x, node *t) {
            item = x;
            next = t;
        }

        node() {
            item = 0;
            next = nullptr;
        }
    };

    using Node = node *;

    Node head;

public:
    list() : head{nullptr} {}

    explicit list(int n) {
        if (n == 0 || n < 1) {
            head = nullptr;
        } else {
            head = new node;
            head->item = 0;
            if (n == 1) {
                head->next = head;
            } else {
                Node tmp = head;
                for (int i = 1; i < n; i++) {
                    tmp->next = new node;
                    tmp->item = i;
                    tmp = tmp->next;
                }
                tmp->next = head;
            }
        }
    };

    Node newNode(Item &i) {
        Node tmp = new node;
        tmp->item = i;
        tmp->next = head;
        head = tmp;
        return tmp;
    }

    // implemented as remove after
    void deleteNextNode(Node x) {
        Node tmp = x->next;
        x->next = tmp->next;
        delete tmp;
    }

    void insert(Node x, Node t) {
        t->next = x->next;
        x->next = t;
    }

    Node remove(Node x) {
        Node t = x->next;
        x->next = t->next;
        return t;
    }

    Node next(Node x) {
        return x->next;
    }

    Item item(Node x) {
        return x->item;
    }

    Item runJosephus(int M) {
        while (head != next(head)) {
            for (int i = 0; i < M; i++) {
                head = next(head);
            }
            deleteNextNode(head);
        }
        return item(head);
    }
};

#endif //CH_4_0_ABSTRACT_DATA_TYPES_LIST_H
