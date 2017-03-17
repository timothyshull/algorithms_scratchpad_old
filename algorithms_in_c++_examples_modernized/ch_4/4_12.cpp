class uf {
public:
    virtual uf(int) = 0;

    virtual int find(int, int) = 0;

    virtual void unite(int, int) = 0;
};

