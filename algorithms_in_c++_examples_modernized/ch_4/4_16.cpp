template<class Item>
class Stack {
private:
    Item* s, * t;
    int n;
public:
    Stack(int maxN)
    {
        s = new Item[maxN];
        n = 0;
        t = new Item[maxN];
        for (int i = 0; i < maxN; ++i) { t[i] = 0; }
    }

    int empty() const { return n == 0; }

    void push(Item item)
    {
        if (t[item] == 1) { return; }
        ++s[n] = item;
        t[item] = 1;
    }

    Item pop()
    {
        t[s[--n]] = 0;
        return s[n];
    }
};

