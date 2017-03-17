template<class Item>
class PQ {
private:
    struct node {
        Item item;
        node* prev, * next;

        node(Item v)
        {
            item = v;
            prev = 0;
            next = 0;
        }
    };

    using link = node*;
    link head, tail;
public:
    using handle = node*;

    PQ(int = 0)
    {
        head = new node(0);
        tail = new node(0);
        head->prev = tail;
        head->next = tail;
        tail->prev = head;
        tail->next = head;
    }

    int empty() const { return head->next->next == head; }

    handle insert(Item v)
    {
        handle t = new node(v);
        t->next = head->next;
        t->next->prev = t;
        t->prev = head;
        head->next = t;
        return t;
    }

    Item getmax();

    void change(handle, Item);

    void remove(handle);

    void join(PQ<Item>&);
};

