#ifndef CH_1_3_LINKED_STACK_H
#define CH_1_3_LINKED_STACK_H

#include <cstdlib>
#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <memory>
#include <sstream>
#include <iostream>

#include "utility.h"

template<typename T>
struct Linked_stack_node;

template<typename T>
struct Linked_stack_node_pointer_traits {
    using node_pointer = Linked_stack_node<T> *;
    using link_pointer = node_pointer;
};

template<typename T>
struct Linked_stack_node {
    // traits
    using Node_traits = Linked_stack_node_pointer_traits<T>;
    using node_pointer = typename Node_traits::node_pointer;
    using link_pointer = typename Node_traits::link_pointer;

    // members
    T value_;
    node_pointer next_;
    // link_pointer prev_;

    // constructors
    inline Linked_stack_node() : next_{nullptr} {}

    inline Linked_stack_node(T item) : next_{nullptr}, value_{item} {}

    // public methods
    std::string to_string() {
        std::stringstream ss;
        ss << "Linked_stack_node(" << value_ << ")";
        return ss.str();
    }
};

template<typename T>
class Linked_stack;

template<typename T>
class Linked_stack_iterator {
    using Node_traits = Linked_stack_node_pointer_traits<T>;
    using link_pointer = typename Node_traits::link_pointer;
    link_pointer ptr_;

    inline explicit Linked_stack_iterator(link_pointer p) noexcept : ptr_{p} {}

    template<class>
    friend
    class Linked_stack;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using reference = value_type &;
    using pointer = value_type *;  // reconsider this
    using difference_type = typename std::pointer_traits<pointer>::difference_type;

    inline Linked_stack_iterator() noexcept : ptr_{nullptr} {}

    inline reference operator*() const {
        return ptr_->value_;
    }

    inline pointer operator->() const {
        return std::pointer_traits<pointer>::pointer_to(ptr_->value_);
    }

    inline Linked_stack_iterator &operator++() {
        ptr_ = ptr_->next_;
        return *this;
    }

    inline Linked_stack_iterator operator++(int) {
        Linked_stack_iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    friend
    inline bool operator==(const Linked_stack_iterator &x, const Linked_stack_iterator &y) { return x.ptr_ == y.ptr_; }

    friend
    inline bool operator!=(const Linked_stack_iterator &x, const Linked_stack_iterator &y) { return !(x == y); }
};

template<typename T>
class Linked_stack {
public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = value_type const *;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;  // check on this because of the relationship with max_size
    using iterator = Linked_stack_iterator<value_type>;

private:
    // private traits
    using node = Linked_stack_node<value_type>;
    using node_pointer = typename node::node_pointer;
    using node_const_pointer = typename node::node_pointer;
    using node_pointer_traits = Linked_stack_node_pointer_traits<value_type>;
    using link_pointer = typename node_pointer_traits::link_pointer;
    using link_const_pointer = link_pointer;
    // private members
    node_pointer first_;
    size_type size_;

public:

    inline Linked_stack() : first_{nullptr}, size_{0} {}

    ~Linked_stack();

    void clear() noexcept;

    inline size_type size() const noexcept { return size_; }

    inline bool empty() const noexcept { return first_ == nullptr; }

    inline iterator begin() noexcept { return iterator{first_}; }

    inline iterator end() noexcept { return iterator{nullptr}; }

    void push(reference item) {
        node_pointer o = first_;
        first_ = new Linked_stack_node<value_type>{item};
        first_->next_ = o;
        size_++;
        utility::assert(check(), "Linked_stack invariant check failed after push");
    }

    value_type pop() {
        if (empty()) {
            throw utility::No_such_element_exception("Linked_stack underflow");
        }
        value_type item = first_->value_;
        node_pointer f = first_;
        first_ = first_->next_;
        delete f;
        size_--;
        utility::assert(check(), "Linked_stack invariant check failed after pop");
        return item;
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "[\n";
        for (auto it = this->begin(); it != this->end(); it++) {
            ss << "    " << it.ptr_->to_string() << "\n";
        }
        ss << "[\n";
        return ss.str();
    }

    bool check() {
        if (size_ < 0) {
            return false;
        }
        if (size_ == 0) {
            if (first_ != nullptr) {
                return false;
            }
        } else if (size_ == 1) {
            if (first_ == nullptr) {
                return false;
            }
            if (first_->next_ != nullptr) {
                return false;
            }
        } else {
            if (first_ == nullptr) {
                return false;
            }
            if (first_->next_ == nullptr) {
                return false;
            }
        }
        int num_nodes = 0;
        for (node_pointer x = first_; x != nullptr && num_nodes <= size_; x = x->next_) {
            num_nodes++;
        }
        return num_nodes == size_;
    }
};

template<> // specialization
class Linked_stack<void> {
public:
    static void main() {
        Linked_stack<std::string> stack;

        for (std::string line; std::getline(std::cin, line) && line != "";) {
            if (line != "-") {
                stack.push(line);
            } else if (!stack.empty()) {
                std::cout << stack.pop() << "\n";
            }
        }
        std::cout << "(" << stack.size() << " nodes remaining on the stack)\n";
    }
};

template<typename T>
Linked_stack<T>::~Linked_stack() {
    clear();
}

template<typename T>
void Linked_stack<T>::clear() noexcept {
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

#endif //CH_1_3_LINKED_STACK_H
