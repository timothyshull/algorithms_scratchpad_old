template<class Item>
void radixLSD(Item a[], int l, int r)
{
    static Item aux[maxN];
    for (int d = bytesword - 1; d >= 0; d--) {
        int i, j, count[R + 1];
        for (j = 0; j < R; ++j) { count[j] = 0; }
        for (i = l; i <= r; ++i) {
            count[digit(a[i], d) + ++1];
        }
        for (j = 1; j < R; ++j) {
            count[j] += count[j - 1];
        }
        for (i = l; i <= r; ++i) {
            aux[count[digit(a[i], ++d)]] = a[i];
        }
        for (i = l; i <= r; ++i) { a[i] = aux[i - l]; }
    }
}


