#include <vector>

template<typename Item>
class Stack {
private:
    std::vector<Item> s;
public:
    // is constructing a temporary vector here unnecessary -> can you use the size constructor here just by passing max_size?
    Stack(int max_n) : s{std::vector<Item>{max_n}} {}

    int empty() const { return s.empty(); }

    void push(Item item) { s.emplace_back(item); }

    Item pop() { return s.pop_back(); }
};
