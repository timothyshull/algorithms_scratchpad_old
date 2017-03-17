#include <iostream>
#include <memory>
#include <cassert>

using namespace std;

typedef struct
{
    int *elems;
    int logLength;
    int allocLength;
} Stack;

void createStack(Stack *s)
{
    s->logLength = 0;
    s->allocLength = 4;
    s->elems = (int *)malloc(4 * sizeof(int));
    assert(s->elems != NULL);
}

void deleteStack(Stack *s)
{
    free(s->elems);
    s->logLength = 0;
    /* free(s) - Don't do this.
      The structure is not dynamically allocated */
}

void pushStack(Stack *s, int value)
{
    if(s->logLength == s->allocLength) {
        /* doubling stratege */
        s->allocLength *= 2;
        s->elems = (int *)realloc(s->elems,s->allocLength * sizeof(int));
        assert(s->elems != NULL);
    }

    s->elems[s->logLength] = value;
    s->logLength++;
}

int popStack(Stack *s)
{
    assert(s->logLength > 0);
    s->logLength--;
    return s->elems[s->logLength];
}

void printStack(Stack *s)
{
    for(int i = 0; i < s->logLength; i++) {
        cout << s->elems[i] << " ";
    }
    cout << endl;
    return;
}

int main()
{
    Stack s;
    createStack(&s);
    for(int i = 0; i < 10; i++) {
        pushStack(&s,i);
    }
    printStack(&s);
    cout << "Pop: " << popStack(&s) << endl;
    printStack(&s);
    cout << "Pop: " << popStack(&s) << endl;
    printStack(&s);

    cout << "Stack disposed" << endl;
    deleteStack(&s);
    printStack(&s);
}




#include <iostream>
#include <memory>
#include <cassert>
#include <cmath>

using namespace std;

#define MYTYPE float

typedef struct {
    void *elems;
    int elemSize;
    int logLength;
    int allocLength;
} Stack;

void createStack(Stack *s, int elemSize)
{
    s->elemSize = elemSize;
    s->logLength = 0;
    s->allocLength = 4;
    s->elems = (int *)malloc(4 * elemSize);
    assert(s->elems != NULL);
}

void deleteStack(Stack *s)
{
    free(s->elems);
    s->logLength = 0;
    /* free(s) - Don't do this.
      The structure is not dynamically allocated */
}

/* make it local or internal */
static void increaseStack(Stack *s)
{
    s->allocLength *= 2;
    s->elems = realloc(s->elems, s->allocLength * s->elemSize);
}

void pushStack(Stack *s, void *elemAddr)
{
    if(s->logLength == s->allocLength)
        increaseStack(s);
    void *target = (char *)s->elems +
                   s->logLength * s->elemSize;
    memcpy(target, elemAddr, s->elemSize);
    s->logLength++;
}

void popStack(Stack *s, void *elemAddr)
{
    void *source =
            (char *)s->elems +
            (s->logLength-1) * s->elemSize;
    memcpy(elemAddr, source, s->elemSize);
    s->logLength--;
}

void printStack(Stack *s)
{
    for(int i = 0; i < s->logLength; i++) {
        cout << *( (MYTYPE*)((char *)s->elems + i * s->elemSize) )<< " ";
    }
    cout << endl;
    return;
}

int main()
{
    Stack s;
    createStack(&s, sizeof(MYTYPE));
    for(int i = 1; i <= 10; i++) {
        MYTYPE f = sqrt(float(i));
        pushStack(&s,&f);
    }
    void *vp = (MYTYPE *)malloc(sizeof(MYTYPE));
    printStack(&s);
    popStack(&s, vp);
    cout << "Pop: " << *((MYTYPE *)vp) << endl;
    printStack(&s);
    popStack(&s, vp);
    cout << "Pop: " << *((MYTYPE *)vp) << endl;
    printStack(&s);

    cout << "Stack disposed" << endl;
    deleteStack(&s);
    printStack(&s);

    free(vp);
}



#include <iostream>
#include <memory>
#include <cassert>

using namespace std;

#define MYTYPE float

typedef struct {
    void *elems;
    int elemSize;
    int logLength;
    int allocLength;
    void (*freefn)(void *);
} Stack;

void freeString(void *elem)
{
    free(*(char **)elem);
}

void createStack(Stack *s, int elemSize, void(*freefn)(void *))
{
    s->elemSize = elemSize;
    s->logLength = 0;
    s->allocLength = 4;
    s->elems = (int *)malloc(4 * elemSize);
    assert(s->elems != NULL);
}

void deleteStack(Stack *s)
{
    if(s->freefn != NULL) {
        for(int i = 0; i < s->logLength; i++){
            s->freefn((char *)s->elems +
                      i * s->elemSize);
        }
    }

    free(s->elems);
    s->logLength = 0;
}

/* make it local or internal */
static void increaseStack(Stack *s)
{
    s->allocLength *= 2;
    s->elems = realloc (s->elems, s->allocLength * s->elemSize);
}

void pushStack(Stack *s, void *elemAddr)
{
    if(s->logLength == s->allocLength)
        increaseStack(s);
    void *target = (char *)s->elems +
                   s->logLength * s->elemSize;
    memcpy(target, elemAddr, s->elemSize);
    s->logLength++;
}

void popStack(Stack *s, void *elemAddr)
{
    void *source =
            (char *)s->elems +
            (s->logLength-1) * s->elemSize;
    memcpy(elemAddr, source, s->elemSize);
    s->logLength--;
}

int main()
{
    const char *friends[] = {"Al", "Bob", "Carl"};
    Stack stringStack;
    createStack(&stringStack, sizeof(char *), freeString);

    for(int i = 0; i < 3; i++) {
        char *cpy = strdup(friends[i]);
        pushStack(&stringStack, &cpy);
    }

    char *name;
    for(int i = 0; i < 3 ; i++) {
        popStack(&stringStack, &name);
        cout << name << endl;
        free(name);  // mem allocated by strdup()
    }
    deleteStack(&stringStack);
}



#include <iostream>
using namespace std;

class Stack
{
public:
    Stack();
    ~Stack();
    explicit Stack(int);
    void push(int);
    int pop();
    bool isEmpty();
    void print();
private:
    int top;  // kind of a stack pointer: 1 up from the current top array index
    int *stackArray;
};

Stack::Stack()
{
    top = 0;
    stackArray = 0;
}

Stack::Stack(int sz)
{
    stackArray = new int[sz];
    top = 0;
}

Stack::~Stack()
{
    delete[] stackArray;
}

void Stack::push(int n)
{
    stackArray[top++] = n;
}

int Stack::pop()
{
    return stackArray[--top];
}

bool Stack::isEmpty()
{
    if(top == 0) return true;
    return false;
}

void Stack::print()
{
    int n = top;
    while(n)
        cout << stackArray[--n] << " ";

    cout << endl;
}

int main()
{
    Stack *st = new Stack(10);
    st->push(10);
    st->push(20);
    st->push(30);
    st->push(40);
    st->push(50);
    st->print();
    st->pop();st->print();
    st->pop();st->print();
    st->pop();st->print();
    cout << "empty:" << st->isEmpty() << endl;
    st->pop();st->print();
    st->pop();st->print();
    cout << "empty:" << st->isEmpty() << endl;
    return 0;
}




#include <iostream>
using namespace std;

template <class T>
class stack
{
private:
    T *stackArray;
    int top;

public:
    stack(int max)
    {
        stackArray = new T[max];
        top = 0;
    }

    void push(T data)
    {
        stackArray[top++] = data;
    }

    T pop()
    {
        return stackArray[--top];
    }

    int empty() const
    {
        return top = 0;
    }
};

int main()
{
    int i;
    stack<int> intStack(10);
    for(i = 0; i < 10; i++) {
        intStack.push(i);
    }
    for(i = 0; i < 10; i++) {
        cout << intStack.pop() << ' ';
    }
    cout << endl;

    stack<char> charStack(10);
    charStack.push('O');
    charStack.push('L');
    charStack.push('I');
    charStack.push('F');
    for(i = 0; i < 4; i++) {
        cout << charStack.pop() << ' ';
    }

    return 0;
}



#include <iostream>

using namespace std;

typedef struct Element {
    int data;
    Element* next;
}Element;

class Stack
{
private:
    Element *top;      // Pointer to the top of regular stack
    Element *topMin;   // Pointer to the top minimum value stack

public:
    Stack();
    ~Stack();
    void push(int);
    int pop();
    int getMinValue();
    void print();
};

Stack::Stack()
{
    top = NULL;
    topMin = NULL;
}

Stack::~Stack()
{
    Element* elm;
    while(top) {
        elm = top->next;
        delete top;
        top = elm;
    }
    while(topMin) {
        elm = topMin->next;
        delete topMin;
        topMin = elm;
    }
}

void Stack::push(int n)
{
    Element *elm = new Element;
    elm->data = n;
    elm->next = top;
    top = elm;

    if(topMin == NULL) {
        elm = new Element;
        elm->data = n;
        elm->next = topMin;
        topMin = elm;
        return;
    }

    if(top->data < topMin->data) {
        elm = new Element;
        elm->data = n;
        elm->next = topMin;
        topMin = elm;
    }
    return;
}

int Stack::pop()
{
    int value;
    Element *elm = top;
    Element *elmMin = topMin;

    if(top == NULL) return NULL;
    elm = top;
    value = elm->data;
    top = elm->next;
    delete elm;

    if(value == topMin->data) {
        elmMin = topMin;
        topMin = elmMin->next;
        delete elmMin;
    }

    return value;
}

int Stack::getMinValue()
{
    if(top) return topMin->data;
    return -1;
}

void Stack::print()
{
    Element *elm;

    elm = top;
    cout << "Regular stack: ";
    while(elm) {
        cout << elm->data << ' ';
        elm = elm->next;
    }
    cout << endl;

    elm = topMin;
    cout << "Minimum stack: ";
    while(elm) {
        cout << elm->data << ' ';
        elm = elm->next;
    }
    cout << endl;
    return;
}

int main()
{
    Stack *st = new Stack;

    st->push(80);
    st->push(70);
    st->push(60);
    st->push(100);
    st->push(40);
    st->push(50);
    st->push(90);
    st->push(10);
    st->push(20);
    st->push(30);

    st->print();
    cout << "Min Value = " << st->getMinValue() << endl << endl;

    for(int i = 0; i < 10; i++) {
        cout << "Popped: " << st->pop() << endl;
        st->print();
        cout << "Min Value = " << st->getMinValue() << endl << endl;
    }

    delete st;

    return 0;
}





#include <iostream>
using namespace std;

template <class T>
class stack
{
private:
    T *stackArray;
    T *stackArrayMin;
    int top, topMin;

public:
    stack() {}

    stack(int max)
    {
        stackArray = new T[max];
        stackArrayMin = new T[max];
        top = 0;
        topMin = 0;
    }

    void push(T data)
    {
        if(top == 0 ) {
            stackArray[top++] = data;
            stackArrayMin[topMin++] = data;
            return;
        }
        if(data < stackArrayMin[topMin-1])
            stackArrayMin[topMin++] = data;
        stackArray[top++] = data;
    }

    T pop()
    {
        if(stackArray[top-1] == stackArrayMin[topMin-1]) topMin--;
        return stackArray[--top];
    }

    T getArrayMinimum()
    {
        return stackArrayMin[topMin-1];
    }

    T empty() const
    {
        return top = 0;
        return topMin = 0;
    }

    void print()
    {
        cout << "stackArray: ";
        for(int i = 0; i < top; i++) {
            cout << stackArray[i] << ' ';
        }
        cout << endl;
        cout << "stackArrayMin: ";
        for(int i = 0; i < topMin; i++) {
            cout << stackArrayMin[i] << ' ';
        }
        cout << endl;
    }
};

int main()
{
    const int Max = 10;
    stack<int> intStack(Max);
    intStack.push(50);
    intStack.push(60);
    intStack.push(40);
    intStack.push(70);
    intStack.push(30);
    intStack.push(80);
    intStack.push(20);
    intStack.push(90);
    intStack.push(0);
    intStack.push(10);

    intStack.print();
    cout << "Minimum: " << intStack.getArrayMinimum() << endl << endl;

    for(int i = 0; i < Max - 1; i++) {
        cout << "pop: " << intStack.pop() << endl;
        intStack.print();
        cout << "Minimum: " << intStack.getArrayMinimum() << endl << endl;
    }

    return 0;
}