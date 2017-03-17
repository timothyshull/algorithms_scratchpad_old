#include <iostream>

using namespace std;

struct node {
    int data;
    node* next;
};

void add(struct node** head, int n) {
    struct node* cur;
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node->data = n;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
        return;
    }

    cur = *head;
    while (cur) {
        if (cur->next == NULL) {
            cur->next = new_node;
            return;
        }
        cur = cur->next;
    }
}

bool isDuplicate(struct node* head, int n) {
    struct node* cur = head;
    while (cur) {
        if (cur->data == n) return true;
        cur = cur->next;
    }
    return false;

}

struct node* getIntersection(struct node* headA, struct node* headB) {
    struct node* curA = headA;
    struct node* curB = headB;
    struct node* result = NULL;
    if (curA == NULL || curB == NULL) return NULL;
    while (curA) {
        while (curB) {
            if (curA->data == curB->data) {
                add(&result, curA->data);
            }
            curB = curB->next;
        }
        curB = headB;
        curA = curA->next;
    }
    return result;
}

struct node* getUnion(struct node* headA, struct node* headB) {
    struct node* cur;
    struct node* result = NULL;
    if (headA == NULL && headB == NULL) return NULL;

    cur = headA;
    while (cur) {
        add(&result, cur->data);
        cur = cur->next;
    }

    cur = headB;
    while (cur) {
        /* check if the new data is already there */
        if (!isDuplicate(result, cur->data)) {
            add(&result, cur->data);
        }
        cur = cur->next;
    }
    return result;
}

void display(struct node* head) {
    if (head == NULL) return;
    struct node* cur = head;
    while (cur) {
        cout << cur->data << ' ';
        cur = cur->next;
    }
    cout << endl;
}

int main() {
    struct node* myListA = NULL;
    struct node* myListB = NULL;
    struct node* intersectionList = NULL;
    struct node* unionList = NULL;

    add(&myListA, 10);
    add(&myListA, 20);
    add(&myListA, 30);
    add(&myListA, 40);
    add(&myListA, 50);
    add(&myListA, 60);
    add(&myListA, 70);
    cout << "List A: ";
    display(myListA);

    add(&myListB, 10);
    add(&myListB, 30);
    add(&myListB, 50);
    add(&myListB, 70);
    add(&myListB, 90);
    add(&myListB, 110);
    add(&myListB, 130);
    cout << "List B: ";
    display(myListB);

    cout << "Intersection of A and B: ";
    intersectionList = getIntersection(myListA, myListB);
    display(intersectionList);

    cout << "Union of A and B: ";
    unionList = getUnion(myListA, myListB);
    display(unionList);

    return 0;
}