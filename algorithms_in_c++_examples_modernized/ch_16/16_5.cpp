template<class Item, class Key>
class ST {
private:
    struct node {
        int m;
        Item b[M];
        int k;

        node()
        {
            m = 0;
            k = 0;
        }
    };

    using link = node*;
    link* dir;
    Item nullItem;
    int N, d, D;
public:
    ST(int maxN)
    {
        N = 0;
        d = 0;
        D = 1;
        dir = new link[D];
        dir[0] = new node;
    }
};

