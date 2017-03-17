#ifndef CH_1_3_LINKED_LIST_H
#define CH_1_3_LINKED_LIST_H

#include <cstdlib>
#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <memory>
#include <sstream>
#include <iostream>

#include "utility.h"

template<typename T>
struct List_node;

template<typename T>
struct List_node_pointer_traits {
    using node_pointer = List_node<T> *;
    using link_pointer = node_pointer;
};

template<typename T>
struct List_node {
    // traits
    using Node_traits = List_node_pointer_traits<T>;
    using node_pointer = typename Node_traits::node_pointer;
    using link_pointer = typename Node_traits::link_pointer;

    // members
    T value_;
    node_pointer next_;
    // link_pointer prev_;

    // constructors
    inline List_node() : next_{nullptr} {}

    // public methods
    std::string to_string() {
        std::stringstream ss;
        ss << "List_node(" << value_ << ")";
        return ss.str();
    }
};

template<typename T>
class Linked_list;

template<typename T>
class Linked_list_iterator {
    using Node_traits = List_node_pointer_traits<T>;
    using link_pointer = typename Node_traits::link_pointer;
    link_pointer ptr_;

    inline explicit Linked_list_iterator(link_pointer p) noexcept : ptr_{p} {}

    template<class>
    friend
    class Linked_list;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using reference = value_type &;
    using pointer = value_type *;  // reconsider this
    using difference_type = typename std::pointer_traits<pointer>::difference_type;

    inline Linked_list_iterator() noexcept : ptr_{nullptr} {}

    inline reference operator*() const {
        return ptr_->value_;
    }

    inline pointer operator->() const {
        return std::pointer_traits<pointer>::pointer_to(ptr_->value_);
    }

    inline Linked_list_iterator &operator++() {
        ptr_ = ptr_->next_;
        return *this;
    }

    inline Linked_list_iterator operator++(int) {
        Linked_list_iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    friend
    inline bool operator==(const Linked_list_iterator &x, const Linked_list_iterator &y) { return x.ptr_ == y.ptr_; }

    friend
    inline bool operator!=(const Linked_list_iterator &x, const Linked_list_iterator &y) { return !(x == y); }
};

template<typename T>
class Linked_list {
public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = value_type const *;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;  // check on this because of the relationship with max_size
    using iterator = Linked_list_iterator<value_type>;

private:
    // private traits
    using node = List_node<value_type>;
    using node_pointer = typename node::node_pointer;
    using node_const_pointer = typename node::node_pointer;
    using node_pointer_traits = List_node_pointer_traits<value_type>;
    using link_pointer = typename node_pointer_traits::link_pointer;
    using link_const_pointer = link_pointer;
    // private members
    node_pointer first_;
    node_pointer last_;
    size_type size_;

public:

    inline Linked_list() : first_{nullptr}, last_{nullptr}, size_{0} {}

    ~Linked_list();

    void clear() noexcept;

    inline size_type size() const noexcept { return size_; }

    inline bool empty() const noexcept { return first_ == nullptr; }

    inline iterator begin() noexcept { return iterator{first_}; }

    inline iterator end() noexcept { return iterator{last_->next_}; }

    value_type peek() {
        if (empty()) {
            throw utility::No_such_element_exception("Linked_list underflow");
        }
        return first_->value_;
    }

    void insert(reference item) {
        node_pointer o = last_;
        last_ = new List_node<value_type>;
        last_->value_ = item;
        if (empty()) {
            first_ = last_;
        } else {
            o->next_ = last_;
        }
        size_++;
        utility::assert(check(), "Linked_list invariant check failed after insert");
    }

    void insert(node_pointer existing, node_pointer to_insert) {
        if (existing == nullptr || to_insert == nullptr) {
            throw utility::No_such_element_exception("Bad insertion");
        }
        to_insert->next_ = existing->next_;
        existing->next_ = to_insert;
    }

    reference remove(node_pointer remove_after) {
        if (remove_after == nullptr) {
            throw utility::No_such_element_exception("Bad node removal");
        }
        node_pointer tmp = remove_after->next_;
        value_type item = tmp->value_;
        remove_after->next_ = tmp->next_;
        delete tmp;
        size_--;
        return item;
    }

    value_type remove() {
        if (empty()) {
            throw utility::No_such_element_exception("remove called on empty list");
        }
        value_type item = first_->value_;
        node_pointer f = first_;
        first_ = first_->next_;
        delete f;
        size_--;
        if (empty()) {
            last_ = nullptr;
        }
        utility::assert(check(), "Linked_list invariant check failed after remove");
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
class Linked_list<void> {
public:
    static void main() {
        Linked_list<std::string> list;

        for (std::string line; std::getline(std::cin, line) && line != "";) {
            if (line != "-") {
                list.insert(line);
            } else if (!list.empty()) {
                std::cout << list.remove() << "\n";
            }
        }
        std::cout << "(" << list.size() << " nodes remaining in list)\n";
    }
};

template<typename T>
Linked_list<T>::~Linked_list() {
    clear();
}

template<typename T>
void Linked_list<T>::clear() noexcept {
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

#endif //CH_1_3_LINKED_LIST_H
