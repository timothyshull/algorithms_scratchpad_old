#include <iostream>

using namespace std;

typedef struct node {
    node* next;
    int data;
} NODE;

class Stack {
public:
    Stack();

    virtual ~Stack();

    virtual void push(int);

    virtual int pop();

    virtual int peekMin();

    int peek();

    friend void print(Stack&);

private:
    bool empty();

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
    top = ptr;
}

int Stack::pop() {
    NODE* tmp = top;
    if (!empty()) {
        int val = top->data;
        top = top->next;
        delete tmp;
        cout << "pop " << val << endl;
        return val;
    }
    else {
        cout << "empty! " << endl;
        return -1;
    }
}

int Stack::peek() {
    if (!empty()) return top->data;
    return -1;
}

bool Stack::empty() {
    if (top == NULL) return true;
    return false;
}

int Stack::peekMin() {
    return -1;
}

void print(Stack& s) {
    NODE* cur = s.top;
    while (cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

class StackWithMin : public Stack {
public:
    StackWithMin();

    ~StackWithMin();

    void push(int);

    int pop();

    int peekMin();

private:
    bool empty();

    NODE* top;
};

StackWithMin::StackWithMin() {
    top = NULL;
}

StackWithMin::~StackWithMin() {
    while (top) {
        NODE* tmp = top;
        top = top->next;
        delete tmp;
    }
}

void StackWithMin::push(int n) {
    if (top) {
        // push only if it's smaller than the top min
        if (n < top->data) {
            NODE* ptr = new NODE;
            ptr->next = top;
            ptr->data = n;
            top = ptr;
        }
    }
        // if empty, just push the new element
    else {
        NODE* ptr = new NODE;
        ptr->next = top;
        ptr->data = n;
        top = ptr;
    }

    Stack::push(n);
}

int StackWithMin::pop() {
    int popped = Stack::pop();
    if (empty()) {
        cout << "empty min stack" << endl;
        return -1;
    }
    if (popped == top->data) {
        NODE* tmp = top;
        if (top->next) {
            top = top->next;
        }
        else {
            top = NULL;
        }
        delete tmp;
    }
    return popped;
}

int StackWithMin::peekMin() {
    if (!empty()) return top->data;
    cout << "empty min stack!" << endl;
    return -1;
}

bool StackWithMin::empty() {
    if (top == NULL) return true;
    return false;
}

int main() {
    Stack* st = new StackWithMin;
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
    st->pop();
    cout << "minimum = " << st->peekMin() << endl;
    print(*st);
    cout << "current top=" << st->peek();
    return 0;
}
