private:

void showR(link h, ostream& os, int d)
{
    if (h->bit <= d) {
        h->item.show(os);
        return;
    }
    showR(h->l, os, h->bit);
    showR(h->r, os, h->bit);
}

public:

void show(ostream& os) { showR(head->l, os, -1); }

