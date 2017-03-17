//
// Created by Timothy Shull on 2/7/16.
//

#ifndef ALGORITHMS_ASSOITER_H
#define ALGORITHMS_ASSOITER_H

#include <iterator>

// class template for insert iterator for associative and unordered containers
template<typename Container>
class asso_insert_iterator : public std::iterator<std::output_iterator_tag, typename Container::value_type> {
protected:
    Container& container;
public:
    // constructor
    // container in which elements are inserted
    explicit asso_insert_iterator(Container& c) : container(c) { }

    // assignment operator
    // - inserts a value into the container asso_insert_iterator<Container>&
    operator=(const typename Container::value_type& value) {
        container.insert(value);
        return *this;
    }

    // dereferencing is a no-op that returns the iterator itself
    asso_insert_iterator<Container>& operator*() {
        return *this;
    }

    // increment operation is a no-op that returns the iterator itself
    asso_insert_iterator<Container>& operator++() {
        return *this;
    }

    asso_insert_iterator<Container>& operator++(int) {
        return *this;
    }
};

// convenience function to create the inserter
template<typename Container>
inline asso_insert_iterator<Container> asso_inserter(Container& c) {
    return asso_insert_iterator<Container>(c);
}

#endif //ALGORITHMS_ASSOITER_H
