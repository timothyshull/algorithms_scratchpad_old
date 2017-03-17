#ifndef ALGORITHMS_BAG_H
#define ALGORITHMS_BAG_H

#include <memory>

using std::size_t;
using std::allocator;
using std::allocator_traits;

template<typename T, typename Allocator = allocator<T>>
class Bag {

private:
    class Node {
    private:
        T item;
        std::shared_ptr<Node> next;
    public:
        Node(const T& value) : next{nullptr}, item{value} { }

        ~Node() {
            if (next)
                delete next;
        }

        std::shared_ptr<Node> getNext() const { return next; }

        const T& getItem() const { return item; }

        void setNext(Node* elem) { next = std::shared_ptr<Node>(elem); }

        void setNext(std::shared_ptr<Node> elem) { next = elem; }

        void setValue(const T& value) { item = value; }
    };

    // Explicit private members
private:
    using Bag_type = Bag<T>;

    std::shared_ptr<Node> first_;
    std::shared_ptr<Node> last_;
    size_type size_{0};

public:
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = std::iterator<pointer, Bag_type>;
    using const_iterator = std::iterator<const_pointer, Bag_type>;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using allocator_type = Allocator;
    using pointer = typename allocator_traits<Allocator>::pointer;
    using const_pointer = typename allocator_traits<Allocator>::const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Bag(std::initializer_list<T> initList) {
        for (auto newItem : initList)
            this->add(newItem);
    }

    void add(T item) {
        std::shared_ptr<Node> old_first = first_;
        first_ = std::make_shared(new Node(item));
        first_.get()->setNext(old_first);
        size_++;

        if (size_ == 1)
            last_ = first_;
    }

    std::shared_ptr<Node> getFirst() const { return first_; }

    std::shared_ptr<Node> getLast() const { return last_; }

    size_type size() const { return size_; }

    bool isEmpty() const { return size_ == 0; }

    iterator begin() { return iterator(this->getFirst().get()->getItem()); }

    const_iterator begin() const { return const_iterator(this->getFirst().get()->getItem()); }

    iterator end() { return iterator(this->getLast().get()->getItem()); }

    const_iterator end() const { return const_iterator(this->getLast().get()->getItem()); }
};

#endif //ALGORITHMS_BAG_H
