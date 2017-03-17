template<class Item>
class GQ {
private:
    vector <Item> s;
    int N;
public:
    GQ(int maxN) : s(maxN + 1), N(0) {}

    int empty() const { return N == 0; }

    void put(Item item) { ++s[N] = item; }

    void update(Item x) {}

    Item get()
    {
        int i = int(N * rand() / (1.0 + RAND_MAX));
        Item t = s[i];
        s[i] = s[N - 1];
        s[N - 1] = t;
        return s[--N];
    }
};


