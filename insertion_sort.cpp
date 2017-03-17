#include <iostream>
#include <iomanip>

using namespace std;

void swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

void insertion(int a[], int sz) {
    for (int i = 1; i < sz; i++) {
        int j = i;
        while (j > 0 && (a[j] < a[j - 1])) {
            swap(a[j], a[j - 1]);
            j--;
        }
        cout << endl;
        for (int k = 0; k < sz; k++) cout << setw(3) << a[k];
    }
}

int main() {
    int a[] = {15, 9, 8, 1, 4, 11, 7, 12, 13, 6, 5, 3, 16, 2, 10, 14};
    int size = sizeof(a) / sizeof(int);
    for (int i = 0; i < size; i++) cout << setw(3) << a[i];
    insertion(a, size);
    cout << endl;
    return 0;
}

using namespace std;

struct List {
    int data;
    struct List* next;
};

void printList(struct List* head) {
    struct List* ptr = head;
    while (ptr) {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << endl;
}

struct List* createList(int a[], int sz) {
    struct List* head = new struct List;
    struct List* current = head;

    for (int i = 0; i < sz; i++) {
        current->data = a[i];
        if (i == sz - 1) {
            current->next = NULL;
            break;
        }
        current->next = new struct List;
        current = current->next;
    }

    return head;
}

// from http://analgorithmaday.blogspot.com/2011/01/insertion-sort-with-linked-listin-place.html

struct List* insertion(struct List* head) {
    if (head == 0) return head;

    // unsorted list - from the 2nd element
    struct List* unsorted = head->next;
    while (unsorted != 0) {
        // take key as an element in the unsorted list.
        struct List* prev = 0;
        struct List* iter = head;
        struct List* key = unsorted;

        // iterate within the sorted list and find the position
        while (iter != 0) {
            if (iter->data < key->data) {
                prev = iter;
                iter = iter->next;
            }
            else
                break;
        }
        unsorted = unsorted->next;
        // if reached the end of sorted list
        if (iter == key)
            continue;

        // note down the position to replace in a sorted list
        struct List* replace = iter;

        //move iter to end of the sorted list
        while (iter->next != key) iter = iter->next;

        // link to the upsorted list
        iter->next = unsorted;

        // delete the key and replace it in sorted list
        if (prev == 0) {
            head = key;
        } else {
            prev->next = key;
        }
        key->next = replace;
        printList(head);
    }
    return head;
}

int main() {
    int a[] = {15, 9, 8, 1, 4, 11, 7, 12, 13, 6, 5, 3, 16, 2, 10, 14};
    int size = sizeof(a) / sizeof(int);

    struct List* head = createList(a, size);
    printList(head);
    head = insertion(head);
    printList(head);

    cout << endl;
    return 0;
}


using namespace std;

void swap(int& x, int& y) {
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
}

void insertion(int a[], int sz) {
    for (int i = 1; i < sz; i++) {
        int j = i;
        while (j > 0) {
            if (a[j - 1] > a[j]) swap(a[j - 1], a[j]);
            j--;
        }
    }
    for (int i = 1; i < sz; i++) cout << a[i] << " ";
}

int main() {
    int a[] = {1, 4, 5, 7, 8, 9, 2, 3, 6, 10, 11};
    int size = sizeof(a) / sizeof(int);
    for (int i = 0; i < size; i++) cout << a[i] << " ";
    cout << "  ==> " << endl;
    insertion(a, size);
    cout << endl;
    return 0;
}
