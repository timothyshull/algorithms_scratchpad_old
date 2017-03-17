private:

char word[maxW];

void matchR(link h, char* v, int i)
{
    if (h == 0) { return; }
    if ((*v == 0) && (h->d == 0)) {
        word[i] = 0;
        std::cout << word << " ";
    }
    if ((*v == '*') || (*v == h->d)) {
        word[i] = h->d;
        matchR(h->m, v + 1, i + 1);
    }
    if ((*v == '*') || (*v < h->d)) {
        matchR(h->l, v, i);
    }
    if ((*v == '*') || (*v > h->d)) {
        matchR(h->r, v, i);
    }
}

public:

void match(char* v) { matchR(head, v, 0); }

