template<class Item>
class PQ {
private:
    // Implementation-dependent code
public:
    PQ(int);

    int empty() const;

    void insert(Item);

    Item getmax();
};

