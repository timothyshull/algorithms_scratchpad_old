#include <iostream>
#include <iomanip>

using namespace std;

#define SIZE 9

/* swap a[i] and a[j] */
void swap(int a[], int i, int j) {
    int temp;
    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void print(const int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        cout << setw(3) << arr[i];
    }
    cout << endl;
}

/* sort arr[left]...arr[right] into increasing order */
void qsort(int a[], int left_index, int right_index) {
    int left, right, pivot;
    if (left_index >= right_index) return;

    left = left_index;
    right = right_index;

    // pivot selection
    pivot = a[(left_index + right_index) / 2];

    // partition
    while (left <= right) {
        while (a[left] < pivot) left++;
        while (a[right] > pivot) right--;
        if (left <= right) {
            swap(a, left, right);
            left++;
            right--;
        }
        print(a);
    }

    // recursion
    qsort(a, left_index, right);
    qsort(a, left, right_index);
}

int main() {
    int a[SIZE] = {1, 12, 5, 26, 7, 14, 3, 7, 2};
    print(a);
    qsort(a, 0, SIZE - 1);
}


using namespace std;

template<class T>
void exchg(T& a, T& b) {
    T tmp = b;
    b = a;
    a = tmp;
}

template<class T>
int partition(T a[], int left, int right) {
    T pivot = a[right];
    int i = left - 1;
    int j = right;
    for (; ;) {
        while (a[--j] > pivot);
        while (a[++i] < pivot);
        if (i >= j) break;
        exchg(a[i], a[j]);
    }
    exchg(a[right], a[i]);
    return i;
}

template<class T>
void quick(T a[], int left, int right) {
    if (left >= right) return;
    int p = partition(a, left, right);
    quick(a, left, p - 1);
    quick(a, p + 1, right);
}

int main() {
    char a[] = {'A', 'S', 'O', 'R', 'T', 'I', 'N', 'G',
                'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    quick(a, 0, sizeof(a) / sizeof(a[0]) - 1);
    return 0;
}