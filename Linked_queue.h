#ifndef CH_1_3_LINKED_QUEUE_H
#define CH_1_3_LINKED_QUEUE_H

#include <cstdlib>
#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <memory>
#include <sstream>
#include <iostream>

#include "utility.h"

template<typename T>
struct Linked_queue_node;

template<typename T>
struct Linked_queue_node_pointer_traits {
    using node_pointer = Linked_queue_node<T> *;
    using link_pointer = node_pointer;
};

template<typename T>
struct Linked_queue_node {
    // traits
    using Node_traits = Linked_queue_node_pointer_traits<T>;
    using node_pointer = typename Node_traits::node_pointer;
    using link_pointer = typename Node_traits::link_pointer;

    // members
    T value_;
    node_pointer next_;
    // link_pointer prev_;

    // constructors
    inline Linked_queue_node() : next_{nullptr} {}

    inline Linked_queue_node(T item) : next_{nullptr}, value_{item} {}

    // public methods
    std::string to_string() {
        std::stringstream ss;
        ss << "List_queue_node(" << value_ << ")";
        return ss.str();
    }
};

template<typename T>
class Linked_queue;

template<typename T>
class Linked_queue_iterator {
    using Node_traits = Linked_queue_node_pointer_traits<T>;
    using link_pointer = typename Node_traits::link_pointer;
    link_pointer ptr_;

    inline explicit Linked_queue_iterator(link_pointer p) noexcept : ptr_{p} {}

    template<class>
    friend
    class Linked_queue;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using reference = value_type &;
    using pointer = value_type *;  // reconsider this
    using difference_type = typename std::pointer_traits<pointer>::difference_type;

    inline Linked_queue_iterator() noexcept : ptr_{nullptr} {}

    inline reference operator*() const {
        return ptr_->value_;
    }

    inline pointer operator->() const {
        return std::pointer_traits<pointer>::pointer_to(ptr_->value_);
    }

    inline Linked_queue_iterator &operator++() {
        ptr_ = ptr_->next_;
        return *this;
    }

    inline Linked_queue_iterator operator++(int) {
        Linked_queue_iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    friend
    inline bool operator==(const Linked_queue_iterator &x, const Linked_queue_iterator &y) { return x.ptr_ == y.ptr_; }

    friend
    inline bool operator!=(const Linked_queue_iterator &x, const Linked_queue_iterator &y) { return !(x == y); }
};

template<typename T>
class Linked_queue {
public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = value_type const *;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;  // check on this because of the relationship with max_size
    using iterator = Linked_queue_iterator<value_type>;

private:
    // private traits
    using node = Linked_queue_node<value_type>;
    using node_pointer = typename node::node_pointer;
    using node_const_pointer = typename node::node_pointer;
    using node_pointer_traits = Linked_queue_node_pointer_traits<value_type>;
    using link_pointer = typename node_pointer_traits::link_pointer;
    using link_const_pointer = link_pointer;
    // private members
    node_pointer first_;
    node_pointer last_;
    size_type size_;

public:

    inline Linked_queue() : first_{nullptr}, last_{nullptr}, size_{0} {}

    ~Linked_queue();

    void clear() noexcept;

    inline size_type size() const noexcept { return size_; }

    inline bool empty() const noexcept { return first_ == nullptr; }

    inline iterator begin() noexcept { return iterator{first_}; }

    inline iterator end() noexcept { return iterator{last_->next_}; }

    value_type peek() {
        if (empty()) {
            throw utility::No_such_element_exception("Linked_queue underflow");
        }
        return first_->value_;
    }

    void enqueue(reference item) {
        node_pointer o = last_;
        last_ = new Linked_queue_node<value_type>{item};
        if (empty()) {
            first_ = last_;
        } else {
            o->next_ = last_;
        }
        size_++;
        utility::assert(check(), "Linked_queue invariant check failed after enqueue");
    }

    value_type dequeue() {
        if (empty()) {
            throw utility::No_such_element_exception("dequeue called on empty Linked_queue");
        }
        value_type item = first_->value_;
        node_pointer f = first_;
        first_ = first_->next_;
        delete f;
        size_--;
        if (empty()) {
            last_ = nullptr;
        }
        utility::assert(check(), "Linked_queue invariant check failed after remove");
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
        } else if (size_ == 0) {
            if (first_ != nullptr || last_ != nullptr) {
                return false;
            }
        } else if (size_ == 1) {
            if (first_ == nullptr || last_ == nullptr) {
                return false;
            }
            if (first_ != last_) {
                return false;
            }
            if (first_->next_ != nullptr) {
                return false;
            }
            int num_nodes = 0;
            for (node_pointer x = first_; x != nullptr && num_nodes <= size_; x = x->next_) {
                num_nodes++;
            }
            if (num_nodes != size_) {
                return false;
            }
            node_pointer ln = first_;
            while (ln->next_ != nullptr) {
                ln = ln->next_;
            }
            if (ln != last_) {
                return false;
            }
        }
        return true;
    }
};

template<> // specialization
class Linked_queue<void> {
public:
    static void main() {
        Linked_queue<std::string> queue;

        for (std::string line; std::getline(std::cin, line) && line != "";) {
            if (line != "-") {
                queue.enqueue(line);
            } else if (!queue.empty()) {
                std::cout << queue.dequeue() << "\n";
            }
        }
        std::cout << "(" << queue.size() << " nodes remaining in queue)\n";
    }
};

template<typename T>
Linked_queue<T>::~Linked_queue() {
    clear();
}

template<typename T>
void Linked_queue<T>::clear() noexcept {
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

#endif //CH_1_3_LINKED_QUEUE_H
