#ifndef TREES_BINARY_SEARCH_TREE_H
#define TREES_BINARY_SEARCH_TREE_H

#include<memory>
#include<sstream>
#include<cstdlib>
#include<cstdio>

#define tassert(x, m) ((x) ? (void)0 : (std::fprintf(stderr, "%s\n", m), std::abort()))

template<typename T, typename U>
constexpr bool is_same() {
    return std::is_same<T, U>::value;
}

class Nullptr_exception : public std::runtime_error {
public:
    inline explicit Nullptr_exception(const std::string &s) : std::runtime_error{s} {}

    inline explicit Nullptr_exception(const char *s) : std::runtime_error{s} {}

    virtual ~Nullptr_exception() noexcept {};
};

class No_such_element_exception : public std::range_error {
public:
    inline explicit No_such_element_exception(const std::string &s) : std::range_error{s} {}

    inline explicit No_such_element_exception(const char *s) : std::range_error{s} {}

    virtual ~No_such_element_exception() noexcept {};
};

template<typename Key_type, typename Value_type>
struct BST_node;

template<typename Key_type, typename Value_type>
struct BST_node_traits {
    using Node_type = BST_node<Key_type, Value_type>;
    using Owning_node_pointer = std::unique_ptr<Node_type>;
    using Shared_node_pointer = std::shared_ptr<Node_type>;
    using Raw_node_pointer = Node_type *;
    using Key_type = Key_type;
    using Value_type = Value_type;
    using Value_type_pointer = std::shared_ptr<Value_type>;
    using Size_type = std::size_t;
};

template<typename Key_type, typename Value_type>
struct BST_node {
    // traits
    using Node_traits = BST_node_traits<Key_type, Value_type>;
    using Node_type = typename Node_traits::Node_type;
    using Owning_node_pointer = typename Node_traits::Owning_node_pointer;
    using Shared_node_pointer = typename Node_traits::Shared_node_pointer;
    using Raw_node_pointer = typename Node_traits::Raw_node_pointer;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;
    using Value_type_pointer = typename Node_traits::Value_type_pointer;
    using Size_type = typename Node_traits::Size_type;

    // members
    Key_type key_;
    Value_type_pointer value_;
    Size_type size_;
    Owning_node_pointer left_;
    Owning_node_pointer right_;

    // constructors
    BST_node(Key_type key, Value_type value, int size) :
            key_{key}, value_{std::make_shared<Node_type>(std::move(value))}, size_{
            static_cast<Size_type>(size)}, left_{nullptr}, right_{nullptr} {};

    BST_node(Key_type key, Value_type_pointer value_ptr, int size) :
            key_{key}, value_{value_ptr}, size_{static_cast<Size_type>(size)}, left_{nullptr}, right_{nullptr} {};

    // public methods
    std::string to_string() {
        std::stringstream ss;
        ss << "BST_node(" << key_ << ": " << value_ << ")";
        return ss.str();
    }
};

template<typename Key_type, typename Value_type>
class Binary_search_tree;

template<typename Key_type, typename Value_type>
class BST_iterator {};

template<typename Key_type, typename Value_type>
class BST_const_iterator {};

template<typename Key_type, typename Value_type>
bool check_invariants(Binary_search_tree<Key_type, Value_type> &tree);

template<typename Key_type, typename Value_type>
class Binary_search_tree {
public:
    using Node_traits = BST_node_traits<Key_type, Value_type>;
    using Node_type = typename Node_traits::Node_type;
    using Owning_node_pointer = typename Node_traits::Owning_node_pointer;
    using Shared_node_pointer = typename Node_traits::Shared_node_pointer;
    using Raw_node_pointer = typename Node_traits::Raw_node_pointer;
    using Key_type = typename Node_traits::Key_type;
    using Value_type = typename Node_traits::Value_type;
    using Value_type_pointer = typename Node_traits::Value_type_pointer;
    using Size_type = typename Node_traits::Size_type;

private:
    Owning_node_pointer root_;

    template<typename Node_pointer>
    Value_type_pointer get(Node_pointer node, Key_type &key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->key_ < key) {
            return get(node->left_, key);
        } else if (key < node->key_) {
            return get(node->right_, key);
        } else {
            return node->value_;
        }
    }

    template<typename Node_pointer>
    Owning_node_pointer put(Node_pointer node, Key_type key, Value_type_pointer value_ptr) {
        if (!node) {
            return std::make_unique<Node_type>(key, value_ptr, 1);
        }
        if (node->key_ < key) {
            return put(node->left_, key, value_ptr);
        } else if (key < node->key_) {
            return put(node->right_, key, value_ptr);
        } else {
            node->value_ = value_ptr;
        }
        node->size = 1 + size(node->left_) + size(node->right_);
        return node;
    }

    template<typename Node_pointer>
    Owning_node_pointer delete_key(Node_pointer node, Key_type key) {
        if (!node) {
            return nullptr;
        }
        if (node->key_ < key) {
            return delete_key(node->left_, key);
        } else if (key < node->key_) {
            return delete_key(node->right_, key);
        } else {
            if (!node->right_) {
                return node->left_;
            }
            if (!node->left_) {
                return node->right_;
            }
            Raw_node_pointer tmp;
            if (is_smart_ptr(node)) {
                tmp = node.get();
            } else {
                tmp = node;
            }
            node = min(tmp->right_);
            node =
        }
        node->size_ = 1 + size(node->left_) + size(node->right_);
        return node;
    }

    template<typename T>
    constexpr bool is_smart_ptr(T t) {
        return is_same<T, Owning_node_pointer>() || is_same<T, Shared_node_pointer>();
    }

public:
    inline bool empty() { return root_ ? root_->size_ == 0 : true; }

    inline Size_type size() { return size(root_); }

    template<typename Node_pointer>
    inline Size_type size(Node_pointer root) { return root_ ? root->size : 0; }

    bool contains(Key_type &key) {
        if (key == nullptr) {
            throw Nullptr_exception{"Binary_search_tree contains() passed a nullptr"};
        }
        // return get(key) != nullptr;
        return get(key) != nullptr;
    }

    Value_type_pointer get(Key_type &key) { return get(root_, key); }

    void put(Key_type &key, Value_type &value) {
        put(key, std::make_unique<Value_type>(std::move(value)));
    }

    void put(Key_type &key, Value_type_pointer value_ptr) {
        if (!value_ptr) {
            delete_key(key);
            return;
        }
        root_ = put(root_, key, value_ptr);
        tassert(check_invariants(*this), "Binary_search_tree invariant check failed after a call to put()");
    }

    void delete_key(Key_type &key) {
        root_ = delete_key(root_, key);
        tassert(check_invariants(*this));
    }
};

template<typename Key_type, typename Value_type>
bool check_invariants(Binary_search_tree<Key_type, Value_type> &tree) {
    return true;
};

#endif //TREES_BINARY_SEARCH_TREE_H
