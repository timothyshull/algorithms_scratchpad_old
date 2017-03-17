template<class Item>
void merge(Item a[], int l, int m, int r)
{
    int N = r - l + 1;  // assuming max_size/2 is m-l+1
    for (int k = N / 2; k > 0; k /= 2) {
        for (int j = k % (N / 2); j + k < N; j += k + k) {
            for (int i = 0; i < k; ++i) {
                compexch(a[l + j + i], a[l + j + i + k]);
            }
        }
    }
}

