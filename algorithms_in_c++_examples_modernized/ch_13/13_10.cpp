private:

void removeR(link t, Key v, int k)
{
    link x = t->next[k];
    if (!(x->item.key() < v)) {
        if (v == x->item.key()) { t->next[k] = x->next[k]; }
        if (k == 0) {
            delete x;
            return;
        }
        removeR(t, v, k - 1);
        return;
    }
    removeR(t->next[k], v, k);
}

public:

void remove(Item x) { removeR(head, x.key(), lgN); }


