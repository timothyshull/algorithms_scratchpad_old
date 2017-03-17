#include <iostream>

using namespace std;

#define MIN(a, b) (a < b ? a : b)

class Stack {
public:
    Stack();

    ~Stack();

    void push(int);

    int pop();

    int peek();

    int peekMin();

    friend void print(Stack&);

private:
    typedef struct node {
        node* next;
        int data;
        int min;
    } NODE;

    NODE* top;
};

Stack::Stack() {
    top = NULL;
}

Stack::~Stack() {
    while (top) {
        NODE* tmp = top;
        top = top->next;
        delete tmp;
    }
}

void Stack::push(int n) {
    NODE* ptr = new NODE;
    ptr->next = top;
    ptr->data = n;
    // currently empty (top is NULL)

    if (top == NULL)
        ptr->min = n;
    else
        ptr->min = MIN(n, top->min);
    top = ptr;
}

int Stack::pop() {
    NODE* tmp = top;
    int val = top->data;
    top = top->next;
    delete tmp;
    cout << "pop " << val << endl;
    return val;
}

int Stack::peek() {
    return top->data;
}

int Stack::peekMin() {
    return top->min;
}

void print(Stack& s) {
    Stack::NODE* cur = s.top;
    while (cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

int main() {
    Stack* st = new Stack;
    st->push(40);
    st->push(50);
    st->push(20);
    st->push(10);
    st->push(30);
    print(*st);
    cout << "minimum = " << st->peekMin() << endl;
    st->pop();
    cout << "minimum = " << st->peekMin() << endl;
    st->pop();
    cout << "minimum = " << st->peekMin() << endl;
    st->pop();
    cout << "minimum = " << st->peekMin() << endl;
    st->pop();
    cout << "minimum = " << st->peekMin() << endl;
    print(*st);
    cout << "current top=" << st->peek();
    return 0;
}