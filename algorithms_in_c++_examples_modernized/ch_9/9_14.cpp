handle insert(Item v)
{
    link t = new node(v), c = t;
    for (int i = 0; i < maxBQsize; ++i) {
        if (c == 0) { break; }
        if (bq[i] == 0) {
            bq[i] = c;
            break;
        }
        c = pair(c, bq[i]);
        bq[i] = 0;
    }
    return t;
}

