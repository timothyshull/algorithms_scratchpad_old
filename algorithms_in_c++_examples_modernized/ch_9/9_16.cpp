static inline int test(int C, int B, int A) { return 4 * C + 2 * B + 1 * A; }

static void BQjoin(link* a, link* b)
{
    link c = 0;
    for (int i = 0; i < maxBQsize; ++i) {
        switch (test(c != 0, b[i] != 0, a[i] != 0)) {
            case 2:
                a[i] = b[i];
                break;
            case 3:
                c = pair(a[i], b[i]);
                a[i] = 0;
                break;
            case 4:
                a[i] = c;
                c = 0;
                break;
            case 5:
                c = pair(c, a[i]);
                a[i] = 0;
                break;
            case 6:
            case 7:
                c = pair(c, b[i]);
                break;
        }
    }
}


