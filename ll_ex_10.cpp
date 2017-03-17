#include <iostream>

using namespace std;

template<typename T>
class List {
    struct Node {
        T data;
        Node* next;

        Node(T d, Node* n = 0) : data(d), next(n) { }
    };

    Node* head;

public:
    List(Node* h = 0) : head(h) { }

    ~List();

    void insert(Node* loc, T d);

    void push_back(T d);

    void push_front(T d);

    T pop_back();

    T pop_front();

    void erase(Node* loc);

    void display();

    Node* search(T d);
};

// destructor
template<typename T>
List<T>::~List() {
    Node* tmp;
    while (head) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}

// insert d before loc
template<typename T>
void List<T>::insert(Node* loc, T d) {
    Node* new_node = new Node(d, 0);
    if (!head) {
        head = new_node;
        return;
    }
    if (loc == head) {
        push_front(d);
        return;
    }
    Node* cur = head;
    while (cur->next) {
        if (cur->next == loc) {
            new_node->next = cur->next;
            cur->next = new_node;
            return;
        }
        cur = cur->next;
    }
}

template<typename T>
void List<T>::push_back(T d) {
    Node* new_node = new Node(d, 0);
    if (!head) {
        head = new_node;
        return;
    }
    Node* cur = head;
    while (cur) {
        if (!cur->next) {
            cur->next = new_node;
            return;
        }
        cur = cur->next;
    }
}

template<typename T>
void List<T>::push_front(T d) {
    Node* new_node = new Node(d, 0);
    if (!head) {
        head = new_node;
        return;
    }
    new_node->next = head;
    head = new_node;
    return;
}

template<typename T>
T List<T>::pop_back() {
    Node* cur = head;
    while (cur) {
        if (!cur->next) {
            T data(cur->data);
            delete cur;
            head = NULL;
            return data;
        }
        else {
            if (!cur->next->next) {
                T data(cur->next->data);
                cur->next = NULL;
                delete cur->next;
                return data;
            }
        }
        cur = cur->next;
    }
    return NULL;
}

template<typename T>
T List<T>::pop_front() {
    if (!head) return NULL;
    Node* tmp = head;
    T data(head->data);
    if (head->next) {
        head = head->next;
        delete tmp;
        return data;
    }
    delete tmp;
    head = NULL;
    return data;
}

template<typename T>
void List<T>::erase(Node* loc) {
    if (loc == head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        return;
    }
    Node* cur = head;
    while (cur) {
        if (cur->next == loc) {
            cur->next = loc->next;
            delete loc;
        }
        cur = cur->next;
    }
}

template<typename T>
typename List<T>::Node* List<T>::search(T d) {
    if (!head) return NULL;
    Node* cur = head;
    while (cur) {
        if (cur->data == d) return cur;
        cur = cur->next;
    }
    return NULL;
}

template<typename T>
void List<T>::display() {
    if (!head) return;
    Node* cur = head;
    while (cur) {
        cout << cur->data << " " << endl;
        cur = cur->next;
    }
    cout << endl;
}

int main() {
    List<int>* myList = new List<int>(NULL);

    cout << "push_back() 20, 30 40, 50\n\n";
    myList->push_back(20);
    myList->push_back(30);
    myList->push_back(40);
    myList->push_back(50);
    myList->display();

    cout << "push_front() 10\n\n";
    myList->push_front(10);
    myList->display();

    cout << "erase 30\n\n";
    myList->erase(myList->search(30));
    myList->display();

    cout << "insert 30 before 40\n\n";
    myList->insert(myList->search(40), 30);
    myList->display();

    cout << "pop_back()\n";
    cout << myList->pop_back() << " just back popped\n\n";
    myList->display();

    cout << "pop_front()\n";
    cout << myList->pop_front() << " just front popped\n\n";
    myList->display();

    return 0;
}