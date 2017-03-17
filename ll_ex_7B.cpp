#include <iostream>

using namespace std;

class Stack {
public:
    Stack();

    ~Stack();

    void push(void* data);

    void* pop();

    void print();

protected:
    typedef struct Element {
        struct Element* next;
        void* data;
    } Element;

    Element* top;
};

Stack::Stack() {
    top = NULL;
}

Stack::~Stack() {
    while (top) {
        Element* elm = top->next;
        delete top;
        top = elm;
    }
}

void Stack::push(void* data) {
    Element* elm = new Element;
    elm->data = data;
    elm->next = top;
    top = elm;
}

void* Stack::pop() {
    void* data;
    if (top == NULL) return data;
    data = top->data;
    Element* elm = top;
    top = elm->next;
    delete elm;
    return data;
}

void Stack::print() {
    Element* elm = top;
    while (elm) {
        cout << *(static_cast<int*>(elm->data)) << " ";
        elm = elm->next;
    }
    cout << endl;
}

int main() {
    Stack* st = new Stack;
    int n1 = 10;
    int n2 = 20;
    int n3 = 30;
    int n4 = 40;
    int n5 = 50;
    st->push(&n1);
    st->push(&n2);
    st->push(&n3);
    st->push(&n4);
    st->push(&n5);
    st->print();
    cout << *(static_cast<int*>(st->pop())) << " poped\n";
    cout << *(static_cast<int*>(st->pop())) << " poped\n";
    st->print();
    cout << endl;
}