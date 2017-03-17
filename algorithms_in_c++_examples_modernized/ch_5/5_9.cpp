void rule(int l, int r, int h)
{
    for (int t = 1, j = 1; t <= h; j += j, ++t) {
        for (int i = 0; l + j + i <= r; i += j + j) {
            mark(l + j + i, t);
        }
    }
}

