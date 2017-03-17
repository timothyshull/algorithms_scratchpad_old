template<class Item>
void batchersort(Item a[], int l, int r)
{
    int N = r - l + 1;
    for (int p = 1; p < N; p += p) {
        for (int k = p; k > 0; k /= 2) {
            for (int j = k % p; j + k < N; j += (k + k)) {
                for (int i = 0; i < N - j - k; ++i) {
                    if ((j + i) / (p + p) == (j + i + k) / (p + p)) {
                        compexch(a[l + j + i], a[l + j + i + k]);
                    }
                }
            }
        }
    }
}

