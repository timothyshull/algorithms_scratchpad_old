#include <iostream>

using namespace std;

void swap(int* n, int* m) {
    int tmp;
    tmp = *m;
    *m = *n;
    *n = tmp;
}

void print(int a[], int sz) {
    for (int i = 0; i < sz; i++) cout << a[i] << " ";
    cout << endl;
}

void SelectionSort(int a[], int sz) {
    int i, j, mn;
    /* traverse the entire array */
    for (i = 0; i < sz; i++) {
        /* find the min */
        mn = i;
        /* compare against all other elements */
        for (j = i + 1; j < sz; j++) {
            if (a[j] < a[mn]) mn = j;
        }
        swap(a[mn], a[i]);
        print(a, sz);
    }
}

int main() {
    int a[] = {4, 6, 9, 1, 2, 0, 8, 7, 5, 3};
    const size_t sz = sizeof(a) / sizeof(a[0]);
    print(a, sz);
    cout << "---------------------\n";
    SelectionSort(a, sz);
}