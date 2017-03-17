#ifndef STACK_H
#define STACK_H

#include <memory>

template<typename Item>
class Stack {
private:
    struct Node {
        Item item;
        std::unique_ptr<Node<Item>> next;

        Node(Item x, Node* t) : item{x}, next{t} {}
    };

    using Link = Node<Item>*;
    std::unique_ptr<Node<Item>> head;
public:
    Stack(int) : head{nullptr} {}

    int empty() const { return head == nullptr; }

    void push(Item x) { head = std::unique_ptr<Node<Item>>{new Node(x, head.get())}; }

    Item pop()
    {
        Item v = head->item;
        auto t = head->next.get();
        head = nullptr;
        head = t;
        return v;
    }
};

#endif //STACK_H
