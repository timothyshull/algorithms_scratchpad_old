#ifndef CUSTOM_ALGORITHMS_SINGLY_LINKED_LIST_H
#define CUSTOM_ALGORITHMS_SINGLY_LINKED_LIST_H

#include <cstddef>
#include <limits>
#include <forward_list>

template<typename T>
class sll_node {
public:
    using value_type = T;
    using pointer = sll_node *;

    sll_node() : item_{0}, next_{nullptr} {}

    sll_node(value_type i, pointer n) : item_{i}, next_{n} {}

    sll_node(value_type i) : item_{i}, next_{nullptr} {}

    friend class singly_linked_list;

private:
    value_type item_;
    pointer next_;
};

template<typename T>
class singly_linked_list {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = T *;
    using const_pointer = T const *;

private:
    using node = sll_node;
    using node_pointer = sll_node *;
    using node_pointer = sll_node const *;

public:
    singly_linked_list() : head_{nullptr}, tail_{nullptr} {}

    ~singly_linked_list() {}

    bool empty() const noexcept { return head_ == nullptr; }

    size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

    void clear() {
        if (!empty()) {
            node_pointer current = head_;
            for (node_pointer p = current; p != nullptr;) {
                node_pointer tmp = p->next_;
                delete (p);
                p = tmp;
            }
            head_ = nullptr;
        }
    }

    node_pointer insert_after(node_pointer p, value_type t) {
        if (p != nullptr) {
            node_pointer tmp = p->next_;
            if (p->next_ != nullptr) {

                p->next_ = new sll_node(t, tmp);
                return p->next_;
            }
        }
        return nullptr;
    }

    void emplace() {}

    void push_back() {}

    void emplace_back() {}

    void pop_back() {}

    void push_front() {}

    void emplace_fron() {}

    void pop_front() {}

    void resize() {}

    void swap() {}

    void merge() {}

    void splice() {}

    void remove() {}

    void remove_if() {}

    void reverse() {}

    void unique() {}

    void sort() {}

private:
    node_pointer head_;
    node_pointer tail_;
};

#endif //CUSTOM_ALGORITHMS_SINGLY_LINKED_LIST_H
