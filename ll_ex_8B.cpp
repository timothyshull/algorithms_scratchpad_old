#include <iostream>

using namespace std;

class Queue {
public:
    Queue();

    ~Queue();

    void push(int);

    int pop();

    void print();

private:
    typedef struct Node {
        Node* next;
        int data;
    } NODE;
    NODE* head;
};

Queue::Queue() {
    head = NULL;
}

Queue::~Queue() {
    if (head == NULL) return;
    NODE* cur = head;
    while (cur) {
        Node* ptr = cur;
        cur = cur->next;
        delete ptr;
    }
}

void Queue::push(int n) {
    if (head == NULL) {
        head = new NODE;
        head->data = n;
        head->next = NULL;
        return;
    }
    NODE* cur = head;
    while (cur) {
        if (cur->next == NULL) {
            NODE* ptr = new NODE;
            ptr->data = n;
            ptr->next = NULL;
            cur->next = ptr;
            return;
        }
        cur = cur->next;
    }
}

void Queue::print() {
    if (head == NULL) return;
    Node* cur = head;
    while (cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

int Queue::pop() {
    if (head == NULL) {
        cout << "empty estack!" << endl;
        return NULL;
    }
    NODE* tmp = head;
    int value = head->data;
    if (head->next) {
        head = head->next;
    }
        // pop the last element (head)
    else {
        delete tmp;
        head = NULL;
    }
    cout << "pop: " << value << endl;;
    return value;
}

int main() {
    Queue* que = new Queue();
    que->push(10);
    que->push(20);
    que->push(30);
    que->push(40);
    que->push(50);
    que->print();
    que->pop();
    que->print();
    que->pop();
    que->print();
    que->pop();
    que->print();
    que->pop();
    que->print();
    que->pop();
    que->print();
    que->pop();
    que->print();
    return 0;
}