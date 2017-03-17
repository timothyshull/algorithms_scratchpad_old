template<class Item>
class Stack {
private:
    struct Node {
        Item item;
        Node* next;

        Node(Item x, Node* t)
        {
            item = x;
            next = t;
        }
    };

    using link = Node*;
    link head;
public:
    Stack(int) { head = 0; }

    int empty() const { return head == 0; }

    void push(Item x) { head = new Node(x, head); }

    Item pop()
    {
        Item v = head->item;
        link t = head->next;
        delete head;
        head = t;
        return v;
    }
};

