template<class Item>
class PQ {
private:
    // Implementation-dependent code
public:
    // Implementation-dependent handle definition
    PQ(int);

    int empty() const;

    handle insert(Item);

    Item getmax();

    void change(handle, Item);

    void remove(handle);

    void join(PQ<Item>&);
};

