#include <iostream>
#include <vector>

using namespace std;

void print(vector<int> v) {
    for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
    cout << endl;
}

vector<int> merge(vector<int> left, vector<int> right) {
    vector<int> result;
    while ((int) left.size() > 0 || (int) right.size() > 0) {
        if ((int) left.size() > 0 && (int) right.size() > 0) {
            if ((int) left.front() <= (int) right.front()) {
                result.push_back((int) left.front());
                left.erase(left.begin());
            }
            else {
                result.push_back((int) right.front());
                right.erase(right.begin());
            }
        } else if ((int) left.size() > 0) {
            for (int i = 0; i < (int) left.size(); i++)
                result.push_back(left[i]);
            break;
        } else if ((int) right.size() > 0) {
            for (int i = 0; i < (int) right.size(); i++)
                result.push_back(right[i]);
            break;
        }
    }
    return result;
}

vector<int> mergeSort(vector<int> m) {
    if (m.size() <= 1)
        return m;

    vector<int> left, right, result;
    int middle = ((int) m.size() + 1) / 2;

    for (int i = 0; i < middle; i++) {
        left.push_back(m[i]);
    }

    for (int i = middle; i < (int) m.size(); i++) {
        right.push_back(m[i]);
    }

    left = mergeSort(left);
    right = mergeSort(right);
    result = merge(left, right);

    return result;
}

int main() {
    vector<int> v;

    v.push_back(38);
    v.push_back(27);
    v.push_back(43);
    v.push_back(3);
    v.push_back(9);
    v.push_back(82);
    v.push_back(10);

    print(v);
    cout << "------------------" << endl;

    v = mergeSort(v);

    print(v);
}

using namespace std;

void print(int a[], int sz) {
    for (int i = 0; i < sz; i++) cout << a[i] << " ";
    cout << endl;
}

void merge(int a[], const int low, const int mid, const int high) {
    int* temp = new int[high - low + 1];

    int left = low;
    int right = mid + 1;
    int current = 0;
    // Merges the two arrays into temp[]
    while (left <= mid && right <= high) {
        if (a[left] <= a[right]) {
            temp[current] = a[left];
            left++;
        }
        else { // if right element is smaller that the left
            temp[current] = a[right];
            right++;
        }
        current++;
    }

    // Completes the array

    // Extreme example a = 1, 2, 3 || 4, 5, 6
    // The temp array has already been filled with 1, 2, 3,
    // So, the right side of array a will be used to fill temp.
    if (left > mid) {
        for (int i = right; i <= high; i++) {
            temp[current] = a[i];
            current++;
        }
    }
        // Extreme example a = 6, 5, 4 || 3, 2, 1
        // The temp array has already been filled with 1, 2, 3
        // So, the left side of array a will be used to fill temp.
    else {
        for (int i = left; i <= mid; i++) {
            temp[current] = a[i];
            current++;
        }
    }
    // into the original array
    for (int i = 0; i <= high - low; i++) {
        a[i + low] = temp[i];
    }
    delete[] temp;
}

void merge_sort(int a[], const int low, const int high) {
    if (low >= high) return;
    int mid = (low + high) / 2;
    merge_sort(a, low, mid);  //left half
    merge_sort(a, mid + 1, high);  //right half
    merge(a, low, mid, high);  //merge them
}

int main() {
    int a[] = {38, 27, 43, 3, 9, 82, 10};
    int arraySize = sizeof(a) / sizeof(int);

    print(a, arraySize);

    merge_sort(a, 0, (arraySize - 1));

    print(a, arraySize);
    return 0;
}


// a: original, b: helper array
void merge(int a[], int b[], int low, int mid, int high) {
    for (int i = low; i <= high; i++) {
        b[i] = a[i];
    }
    int left = low;
    int right = mid + 1;
    int index = low;
    while (left <= mid && right <= high) {
        if (b[left] <= b[right])
            a[index++] = b[left++];
        else
            a[index++] = b[right++];
    }

    // copy remainder of the left side
    int remainder = mid - left + 1;
    for (int i = 0; i < remainder; i++) {
        a[index + i] = b[left + i];
    }
}

// merge sort starts here
void mergeSort(int a[], int b[], int low, int high) {
    if (low >= high) return;
    int mid = (low + high) / 2;
    mergeSort(a, b, low, mid);
    mergeSort(a, b, mid + 1, high);
    merge(a, b, low, mid, high);
}

// prepare for real mergesort()
void mergeSort(int a[], int len) {
    int* b = new int[len];
    mergeSort(a, b, 0, len - 1);
    delete[] b;
}

int main() {
    int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int size = sizeof(a) / sizeof(int);
    mergeSort(a, size);

    return 0;
}


#define N 2  /* # of thread */

int a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};  /* target array */

/* structure for array index
 * used to keep low/high end of sub arrays
 */
typedef struct Arr {
    int low;
    int high;
} ArrayIndex;

void merge(int low, int high) {
    int mid = (low + high) / 2;
    int left = low;
    int right = mid + 1;

    int b[high - low + 1];
    int i, cur = 0;

    while (left <= mid && right <= high) {
        if (a[left] > a[right])
            b[cur++] = a[right++];
        else
            b[cur++] = a[right++];
    }

    while (left <= mid) b[cur++] = a[left++];
    while (right <= high) b[cur++] = a[left++];
    for (i = 0; i < (high - low + 1); i++) a[low + i] = b[i];
}

void* mergesort(void* a) {
    ArrayIndex* pa = (ArrayIndex*) a;
    int mid = (pa->low + pa->high) / 2;

    ArrayIndex aIndex[N];
    pthread_t thread[N];

    aIndex[0].low = pa->low;
    aIndex[0].high = mid;

    aIndex[1].low = mid + 1;
    aIndex[1].high = pa->high;

    if (pa->low >= pa->high) return;

    int i;
    for (i = 0; i < N; i++) pthread_create(&thread[i], NULL, mergesort, &aIndex[i]);
    for (i = 0; i < N; i++) pthread_join(thread[i], NULL);

    merge(pa->low, pa->high);

    pthread_exit(NULL);
}

int main() {
    ArrayIndex ai;
    ai.low = 0;
    ai.high = sizeof(a) / sizeof(a[0]) - 1;
    pthread_t thread;

    pthread_create(&thread, NULL, mergesort, &ai);
    pthread_join(thread, NULL);

    int i;
    for (i = 0; i < 10; i++) printf("%d ", a[i]);

    return 0;
}
