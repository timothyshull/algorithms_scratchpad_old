#include <iostream>

using namespace std;

typedef struct PriorityQueue {
    int data;
    int pri;
    PriorityQueue* next;
} pQ;

class PQueue {
public:
    PQueue();

    ~PQueue();

    void push(int, int);

    int pop();

    void display();

private:
    pQ* head;
};

PQueue::PQueue() {
    head = NULL;
}

void PQueue::push(int d, int pri) {
    pQ* ptr = new pQ;
    ptr->data = d;
    ptr->pri = pri;
    ptr->next = NULL;

    if (head == NULL) {
        head = ptr;
        return;
    }

    pQ* cur = head;
    pQ* prev = head;
    while (cur) {
        if (pri > cur->pri) {
            if (cur == head) {
                pQ* old = head;
                head = ptr;
                head->next = old;
                return;
            }
            prev->next = ptr;
            ptr->next = cur;
            return;
        }
        if (cur->next == NULL) {
            cur->next = ptr;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

int PQueue::pop() {
    if (head == NULL) return -1;
    int val = head->data;
    pQ* old = head;
    if (head->next) {
        head = head->next;
        delete old;
    }
    return val;
}

void PQueue::display() {
    pQ* cur = head;
    while (cur) {
        cout << cur->data << ":" << cur->pri << endl;
        cur = cur->next;
    }
}

int main() {
    PQueue* myPQueue = new PQueue();
    myPQueue->push(4, 400);
    myPQueue->push(5, 500);
    myPQueue->push(1, 100);
    myPQueue->push(2, 200);
    myPQueue->push(3, 300);

    myPQueue->display();

    cout << "pop " << myPQueue->pop() << endl;
    cout << "pop " << myPQueue->pop() << endl;
    cout << "pop " << myPQueue->pop() << endl;
    cout << "pop " << myPQueue->pop() << endl;
    cout << "pop " << myPQueue->pop() << endl;

    return 0;
}


using namespace std;

void swap(int&, int&);

class PQueue {
public:
    PQueue(int sz) : N(0) { pq = new int[sz]; }

    ~PQueue() { delete[] pq; }

    void insert(int item) { pq[++N] = item; }

    int remove();

    bool isEmpty() { return N == 0; }

    void display();

private:
    int* pq;
    int N;
};

int PQueue::remove() {
    int max = 0;
    for (int i = 1; i <= N; i++)
        if (pq[max] < pq[i]) max = i;
    /* swap the max item with the last item */
    swap(pq[max], pq[N]);
    /* return the last item which is not the max,
       then reduce the array size by 1 */
    return pq[N--];
}

void PQueue::display() {
    for (int i = 1; i <= N; i++) cout << pq[i] << " ";
    cout << endl;
}

void swap(int& a, int& b) {
    int temp = b;
    b = a;
    a = temp;
}

int main() {
    // first item of array a is not used
    int a[] = {0, 19, 17, 16, 12, 9, 15, 1, 2, 11, 7, 3, 10, 14};
    int sz = sizeof(a) / sizeof(a[0]);
    PQueue* q = new PQueue(sz - 1);

    for (int i = 1; i < sz; i++) {
        q->insert(a[i]);
    }

    q->display();

    for (int i = 1; i < sz; i++) {
        cout << "remove max " << q->remove() << endl;
        q->display();
    }

    return 0;
}


using namespace std;

void swap(int&, int&);

class PQueue {
public:
    PQueue(int sz) : N(0) { pq = new int[sz]; }

    ~PQueue() { delete[] pq; }

    void insert(int);

    int remove();

    bool isEmpty() { return N == 0; }

    void display();

    void siftDown(int*, int, int);

    void siftUp(int*, int);

private:
    int* pq;
    int N;
};

void PQueue::siftUp(int a[], int k) {
    while (k > 1 && a[k] > a[k / 2]) {
        swap(a[k], a[k / 2]);
        k = k / 2;
    }
}

void PQueue::siftDown(int a[], int k, int n) {
    while (2 * k <= n) {
        int child = 2 * k;
        if (child < n && a[child] < a[child + 1]) child++;
        if (a[k] < a[child]) {
            swap(a[k], a[child]);
            k = child;
        }
        else
            return;
    }
}

void PQueue::insert(int item) {
    pq[++N] = item;
    siftUp(pq, N); // N is the last index
}

// remove max element
int PQueue::remove() {
    swap(pq[N], pq[1]);
    // N is the last index, pq[N] is the max about to be removed
    siftDown(pq, 1, N - 1);  // move down
    return pq[N--];  // Now, N is the max item index
}

void PQueue::display() {
    for (int i = 1; i <= N; i++) cout << pq[i] << " ";
    cout << endl;
}

void swap(int& a, int& b) {
    int temp = b;
    b = a;
    a = temp;
}

int main() {
    int a[] = {0, 19, 17, 16, 12, 9, 15, 1, 2, 11, 7, 3, 10, 14};
    int sz = sizeof(a) / sizeof(a[0]);
    PQueue* q = new PQueue(sz - 1);

    for (int i = 1; i < sz; i++) {
        q->insert(a[i]);
    }

    q->display();

    for (int i = 1; i < sz; i++) {
        cout << "remove max " << q->remove() << endl;
        q->display();
    }

    return 0;
}
