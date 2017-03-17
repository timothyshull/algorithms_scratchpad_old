template<class Item>
class QUEUE {
private:
    // Implementation-dependent code
public:
    QUEUE(int);

    QUEUE(const QUEUE&);

    QUEUE& operator=(const QUEUE&);

    ~QUEUE();

    int empty() const;

    void put(Item);

    Item get();
};

