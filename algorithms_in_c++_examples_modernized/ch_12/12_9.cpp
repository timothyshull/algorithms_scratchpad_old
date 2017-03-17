private:

void showR(link h, ostream& os)
{
    if (h == 0) { return; }
    showR(h->l, os);
    h->item.show(os);
    showR(h->r, os);
}

public:

void show(ostream& os) { showR(head, os); }

