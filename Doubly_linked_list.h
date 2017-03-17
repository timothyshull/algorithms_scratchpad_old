#ifndef LISTS_DOUBLY_LINKED_LIST_H
#define LISTS_DOUBLY_LINKED_LIST_H

#include <memory>

template<typename T>
using raw_unowned_pointer = T;

template<typename T>
struct DLL_node;

template<typename T>
struct DLL_node_traits {
    using Node_type = DLL_node<T>;
    using Node_pointer = raw_unowned_pointer<Node_type*>;
    using Forward_link = std::unique_ptr<Node_type>;
    using Previous_link = Node_pointer;
};

template<typename T>
struct DLL_node {
    using Node_traits = DLL_node_traits<T>;
    using Node_type = typename Node_traits::Node_type;
    using Node_pointer = typename Node_traits::Node_pointer;
    using Forward_link = typename Node_traits::Forward_link;
    using Previous_link = typename Node_traits::Previous_link;

    // members
    T _value;
    Forward_link _next;
    Previous_link _prev;

    DLL_node() : _next{nullptr}, _prev{nullptr} {}

    DLL_node(const T& value, Node_pointer next, Node_pointer prev) : _value{value}, _next{next}, _prev{prev} {}
};

template<typename T>
class Doubly_linked_list {
public:
    using Node_traits = DLL_node_traits<T>;
    using Node_type = typename Node_traits::Node_type;
    using Node_pointer = typename Node_traits::Node_pointer;
    using Forward_link = typename Node_traits::Forward_link;
    using Previous_link = typename Node_traits::Previous_link;

    Doubly_linked_list() : _head{nullptr}, _tail{nullptr} {}

    void push_back(const T&);

    T pop_back();

private:
    Forward_link _head;
    Node_pointer _tail;
};

template<typename T>
void Doubly_linked_list<T>::push_back(const T& value)
{
    if (_tail != nullptr) {
        _tail->_next = std::make_unique<Node_type>(value, nullptr, _tail);
        _tail = _tail->_next.get();
    } else {
        _head = std::make_unique<Node_type>(value, nullptr, nullptr);
        _tail = _head.get();
    }
}

template<typename T>
T Doubly_linked_list<T>::pop_back()
{
    if (!_tail) {
        throw std::exception(); // empty list
    }

    T return_val{_tail->_value};
    if (_head.get() == _tail) {
        _head.reset();
        _head = nullptr;
        _tail = nullptr;
    } else {
        _tail = _tail->_prev;
    }
    return return_val;
}

#endif //LISTS_DOUBLY_LINKED_LIST_H
