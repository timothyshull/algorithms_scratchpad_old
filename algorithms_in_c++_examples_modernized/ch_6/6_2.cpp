template<class Item>
void selection(Item a[], int l, int r)
{
    for (int i = l; i < r; ++i) {
        int min = i;
        for (int j = i + 1; j <= r; ++j) {
            if (a[j] < a[min]) { min = j; }
        }
        exch(a[i], a[min]);
    }
}
