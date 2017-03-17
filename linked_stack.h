//
// Created by Timothy Shull on 4/27/16.
//

#ifndef ALGS_CPP_LINKED_STACK_H
#define ALGS_CPP_LINKED_STACK_H

#include <cstddef>
#include <string>

using std::string;

template<typename T>
class node {
    using value_type = T;
    using node_pointer = node<T> *;

    value_type item;
    node_pointer next;

    friend class linked_stack;
    friend class linked_stack_iterator;
};

template <typename T>
class linked_stack_iterator {
public:
    using node_pointer = node<T> *;
private:
    node_pointer current;
public:
    linked_stack_iterator();
    bool has_next();
    void remove();
    node_pointer next();
};

template<typename T>
class linked_stack {
public:
    using value_type = T;
    using node_pointer = node<T> *;
    using size_type = size_t;
    using iterator = linked_stack_iterator<T>;
private:
    size_type N;
    node_pointer first;

    bool check();
public:
    linked_stack();
    bool is_empty();
    size_type size();
    void push();
    value_type pop();
    value_type peek();
    string to_string();
};


#endif //ALGS_CPP_LINKED_STACK_H
