#ifndef ALGORITHMS_BAG_H
#define ALGORITHMS_BAG_H

template <typename T> class bag;

template <typename T>
class bag_node {
    T value;
    bag_node* next;
};

#endif //ALGORITHMS_BAG_H
