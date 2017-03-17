#ifndef LIST_H
#define LIST_H

#include <memory>

// assumes a C style list interface

template<typename Item_type>
struct Node {
    Node(Item_type x, std::shared_ptr<Node<Item_type>>& t) : item{x}, next{t} {}

    Node(Item_type x, std::shared_ptr<Node<Item_type>>&& t) : item{x}, next{t} {}

    ~Node() = default;

    Item_type item;
    std::shared_ptr<Node<Item_type>> next;
};

template<typename Item_type>
using Link = std::shared_ptr<Node<Item_type>>;

template<typename Item_type>
using Raw_node_pointer<Item_type> = Node<Item_type>*;

template<typename Item_type>
void construct(int);

template<typename Item_type>
Raw_node_pointer<Item_type> new_node(int);

template<typename Item_type>
void delete_node(Node<Item_type>);

template<typename Item_type>
void insert(Node<Item_type>, Node<Item_type>);

template<typename Item_type>
void remove(Node<Item_type>);

template<typename Item_type>
inline Raw_node_pointer<Item_type> next(Raw_node_pointer<Item_type> x) noexcept { return x ? x->next.get() : nullptr; }

template<typename Item_type>
inline Item_type item(Raw_node_pointer<Item_type> x) { return x->item; };

#endif // LIST_H
