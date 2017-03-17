#include <string>

class ST {
    int N, val;

    struct node {
        int v, d;
        node* l, * m, * r;

        node(int d) : v(-1), d(d), l(0), m(0), r(0) {}
    };

    using link = node*;
    link head;

    link indexR(link h, const string& s, int w)
    {
        int i = s[w];
        if (h == 0) { h = new node(i); }
        if (i == 0) {
            if (h->v == -1) { h->v = ++N; }
            val = h->v;
            return h;
        }
        if (i < h->d) { h->l = indexR(h->l, s, w); }
        if (i == h->d) { h->m = indexR(h->m, s, w + 1); }
        if (i > h->d) { h->r = indexR(h->r, s, w); }
        return h;
    }

public:
    ST() : head(0), N(0) {}

    int index(const string& key)
    {
        head = indexR(head, key, 0);
        return val;
    }
};

