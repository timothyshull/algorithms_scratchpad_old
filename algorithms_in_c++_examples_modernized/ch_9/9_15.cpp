Item getmax()
{
    int i, max;
    Item v = 0;
    link* temp = new link[maxBQsize];
    for (i = 0, max = -1; i < maxBQsize; ++i) {
        if (bq[i] != 0) {
            if ((max == -1) || (v < bq[i]->item)) {
                max = i;
                v = bq[max]->item;
            }
        }
    }
    link x = bq[max]->l;
    for (i = max; i < maxBQsize; ++i) { temp[i] = 0; }
    for (i = max; i > 0; i--) {
        temp[i - 1] = x;
        x = x->r;
        temp[i - 1]->r = 0;
    }
    delete bq[max];
    bq[max] = 0;
    BQjoin(bq, temp);
    delete temp;
    return v;
}

