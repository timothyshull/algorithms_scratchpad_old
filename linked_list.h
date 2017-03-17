#ifndef LINKEDLISTS_LINKED_LIST_H
#define LINKEDLISTS_LINKED_LIST_H

#include <memory>

#include <forward_list>

template<typename NodeType>
class LinkedListIterator;

template<typename ValueType>
class LinkedList;

template<typename ValueType>
class LinkedListNode {
public:
    using node_pointer_type = typename std::unique_ptr<LinkedListNode<ValueType>>;
    using value_type = ValueType;

    template<typename>
    friend
    class LinkedListIterator;

    template<typename>
    friend
    class LinkedList;

    LinkedListNode() = default;

    LinkedListNode(ValueType value);

private:
    value_type value;
    node_pointer_type next;
};

template<typename ValueType>
LinkedListNode::LinkedListNode(ValueType v) : value{v}, next{nullptr} {};

template<typename NodePointerType>
class LinkedListIterator {
public:
    using node_type = typename std::pointer_traits<NodePointerType>::element_type;
    using node_pointer_type = NodePointerType;
    using iterator_category = std::forward_iterator_tag;
    using value_type = node_type::value_type;
    using reference = value_type &;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;

    LinkedListIterator() = default;

    LinkedListIterator(NodePointerType start) : current{start} {};

//    NodePointerType next();

    reference operator*() const { return current->value; }

    pointer operator->() const {
        return &(current->value);
    }

    LinkedListIterator &operator++() {
        current = current->next;
        return *this;
    }

    LinkedListIterator operator++(int) {
        LinkedListIterator tmp{*this};
        ++(*this);
        return tmp;
    }

    friend
    bool operator==(const LinkedListIterator &x, const LinkedListIterator &y) { return x.current == y.current; }

    friend
    bool operator!=(const LinkedListIterator &x, const LinkedListIterator &y) { return !(x == y); }

private:
    node_pointer_type current;
};

template<typename ValueType>
class LinkedList {
    using node_type = LinkedListNode<ValueType>;
    using unique_node_pointer_type = typename std::unique_ptr<LinkedListNode<ValueType>>;
    using raw_node_pointer_type = LinkedListNode<ValueType> *;

public:
    using value_type = ValueType;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using iterator = LinkedListIterator<raw_node_pointer_type>;

    LinkedList() = default;

    LinkedList();

private:
    unique_node_pointer_type first;
    raw_node_pointer_type last;
};


#endif //LINKEDLISTS_LINKED_LIST_H
