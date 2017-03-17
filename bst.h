#ifndef ALGORITHMS_MASTER_BST_H
#define ALGORITHMS_MASTER_BST_H

#include <memory>

template <typename KeyType, typename ValueType>
class BSTNode {
public:
    using key_type = KeyType;
    using value_type = ValueType;
    using parent_node = BSTNode<KeyType, ValueType> *;
    using child_node = std::unique_ptr<BSTNode<KeyType, ValueType>>;

    BSTNode() = default;

    BSTNode(KeyType k, ValueType v, int s) : key{k}, value{v}, size{s} {};

private:
    KeyType key;
    ValueType value;
    child_node left;
    child_node right;
    int size;
};

#endif //ALGORITHMS_MASTER_BST_H
