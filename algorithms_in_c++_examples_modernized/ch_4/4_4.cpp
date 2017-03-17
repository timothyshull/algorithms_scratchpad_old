template<typename Item>
class Stack {
private:
    // Implementation-dependent code
public:
    Stack(int);

    int empty() const;

    void push(Item item);

    Item pop();
};

