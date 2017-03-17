#ifndef CH_1_3_LINKED_BAG_H
#define CH_1_3_LINKED_BAG_H

#include <cstdlib>
#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <memory>
#include <sstream>
#include <iostream>

template<typename T>
struct Linked_bag_node;

template<typename T>
struct Linked_bag_node_pointer_traits {
    using node_pointer = Linked_bag_node<T> *;
    using link_pointer = node_pointer;
};

template<typename T>
struct Linked_bag_node {
    // traits
    using Node_traits = Linked_bag_node_pointer_traits<T>;
    using node_pointer = typename Node_traits::node_pointer;
    using link_pointer = typename Node_traits::link_pointer;

    // members
    T value_;
    node_pointer next_;
    // link_pointer prev_;

    // constructors
    inline Linked_bag_node() : next_{nullptr} {}

    inline Linked_bag_node(T item) : next_{nullptr}, value_{item} {}

};

template<typename T>
class Linked_bag;

template<typename T>
class Linked_bag_iterator {
    using Node_traits = Linked_bag_node_pointer_traits<T>;
    using link_pointer = typename Node_traits::link_pointer;
    link_pointer ptr_;

    inline explicit Linked_bag_iterator(link_pointer p) noexcept : ptr_{p} {}

    template<class>
    friend
    class Linked_bag;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using reference = value_type &;
    using pointer = value_type *;  // reconsider this
    using difference_type = typename std::pointer_traits<pointer>::difference_type;

    inline Linked_bag_iterator() noexcept : ptr_{nullptr} {}

    inline reference operator*() const {
        return ptr_->value_;
    }

    inline pointer operator->() const {
        return std::pointer_traits<pointer>::pointer_to(ptr_->value_);
    }

    inline Linked_bag_iterator &operator++() {
        ptr_ = ptr_->next_;
        return *this;
    }

    inline Linked_bag_iterator operator++(int) {
        Linked_bag_iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    friend
    inline bool operator==(const Linked_bag_iterator &x, const Linked_bag_iterator &y) { return x.ptr_ == y.ptr_; }

    friend
    inline bool operator!=(const Linked_bag_iterator &x, const Linked_bag_iterator &y) { return !(x == y); }
};

template<typename T>
class Linked_bag {
public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = value_type const *;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;  // check on this because of the relationship with max_size
    using iterator = Linked_bag_iterator<value_type>;

private:
    // private traits
    using node = Linked_bag_node<value_type>;
    using node_pointer = typename node::node_pointer;
    using node_const_pointer = typename node::node_pointer;
    using node_pointer_traits = Linked_bag_node_pointer_traits<value_type>;
    using link_pointer = typename node_pointer_traits::link_pointer;
    using link_const_pointer = link_pointer;
    // private members
    node_pointer first_;
    size_type size_;

public:

    inline Linked_bag() : first_{nullptr}, size_{0} {}

    ~Linked_bag();

    void clear() noexcept;

    inline size_type size() const noexcept { return size_; }

    inline bool empty() const noexcept { return first_ == nullptr; }

    inline iterator begin() noexcept { return iterator{first_}; }

    inline iterator end() noexcept { return iterator{nullptr}; }

    void add(reference item) {
        node_pointer o = first_;
        first_ = new Linked_bag_node<value_type>{item};
        first_->next_ = o;
        size_++;
    }
};

template<> // specialization
class Linked_bag<void> {
public:
    static void main() {
        Linked_bag<std::string> bag;

        for (std::string line; std::getline(std::cin, line) && line != "";) {
            bag.add(line);
        }
        std::cout << "The size of the bag is: " << bag.size() << "\n";

        for (auto s : bag) {
            std::cout << s << "\n";
        }
    }
};

template<typename T>
Linked_bag<T>::~Linked_bag() {
    clear();
}

template<typename T>
void Linked_bag<T>::clear() noexcept {
    if (!empty()) {
        link_pointer f = first_;
        size_ = 0;
        while (f != nullptr) {
            node_pointer np = f;
            f = f->next_;
            delete np;
        }
    }
}

#endif //CH_1_3_LINKED_BAG_H
