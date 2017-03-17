#ifndef LISTS_SIMPLIFIED_STD_LIST_H
#define LISTS_SIMPLIFIED_STD_LIST_H

#include <memory>
#include <type_traits>

using std::pointer_traits;
using std::allocator;

// forward declarations
template<typename T, typename Void_ptr>
struct list_node;

template<typename T, typename Void_ptr>
struct list_node_base;

// traits
template<typename T, typename Void_ptr>
struct list_node_pointer_traits {
    using node_pointer = typedef typename pointer_traits<Void_ptr>::template rebind<list_node<T, Void_ptr>>;
    using base_pointer = typedef typename pointer_traits<Void_ptr>::template rebind<list_node_base<T, Void_ptr>>;
    using link_pointer = std::conditional<std::is_pointer<Void_ptr>::value, base_pointer, node_pointer>::type;
    using non_link_pointer = std::conditional<std::is_same<link_pointer, node_pointer>::value, base_pointer, node_pointer>::type;

    static inline link_pointer unsafe_link_pointer_cast(link_pointer p) { return p; }

    static inline link_pointer
    unsafe_link_pointer_cast(non_link_pointer p) { return static_cast<link_pointer>(static_cast<Void_ptr>(p)); }
};

// base node
template<typename T, typename Void_ptr>
struct list_node_base {
    // traits
    using Node_traits = list_node_pointer_traits<T, Void_ptr>;
    using node_pointer = Node_traits::node_pointer;
    using base_pointer = Node_traits::base_pointer;
    using link_pointer = Node_traits::link_pointer;

    // members
    link_pointer _prev;
    link_pointer _next;

    // constructors
    inline list_node_base() : _prev{Node_traits::unsafe_link_pointer_cast(_self())},
                              _next{Node_traits::unsafe_link_pointer_cast(_self())} {}

    // helpers
    inline base_pointer _self() { return pointer_traits<base_pointer>::pointer_to(*this); }

    inline node_pointer _base_as_node() { return static_cast<node_pointer>(_self()); }
};

// node
template<typename T, typename Void_ptr>
struct list_node : public list_node_base<T, Void_ptr> {
    // traits
    using base_type = list_node_base<T, Void_ptr>;
    using link_pointer  = base_type::link_pointer;

    // member
    T _value;

    // helpers
    inline link_pointer _node_as_link() { return static_cast<link_pointer>(base_type::_self()); }
};

// forward declarations
template<typename T, typename Allocator = allocator<T>>
class list;

template<class T, class Void_ptr>
class list_const_iterator;

// basic iterator
template<class T, class Void_ptr>
class list_iterator {
    // traits
    using Node_traits = list_node_pointer_traits<T, Void_ptr>;
    using link_pointer = Node_traits::link_pointer;

    // member
    link_pointer _ptr;

    // private constructor
    inline explicit list_iterator(link_pointer p) noexcept : _ptr{p} {}

    // friend declarations
    template<class, class>
    friend
    class list;

    template<class, class>
    friend
    class list_const_iterator;

public:
    // traits
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using reference = value_type &;
    using pointer = value_type *;
    using difference_type = pointer_traits<pointer>::difference_type;

    // constructor
    inline list_iterator() noexcept : _ptr{nullptr} {}

    // operator overloads
    inline reference operator*() const { return _ptr->_base_as_node()->_value; }

    inline pointer operator->() const { return std::addressof(_ptr->_base_as_node()->_value); }

    inline list_iterator &operator++() {
        _ptr = _ptr->_next;
        return *this;
    }

    inline list_iterator &operator++(int) {
        list_iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    inline list_iterator &operator--() {
        _ptr = _ptr->_prev;
        return *this;
    }

    inline list_iterator &operator--(int) {
        list_iterator tmp(*this);
        --(*this);
        return tmp;
    }

    friend
    inline bool operator==(const list_iterator &x, const list_iterator &y) { return x._ptr == y._ptr; }

    friend
    inline bool operator!=(const list_iterator &x, const list_iterator &y) { return !(x == y); }
};

// const iterator
template<class T, class Void_ptr>
class list_const_iterator {
    // traits
    using Node_traits = list_node_pointer_traits<T, Void_ptr>;
    using link_pointer = Node_traits::link_pointer;

    // member
    link_pointer _ptr;

    // private constructor
    inline explicit list_const_iterator(link_pointer p) noexcept : _ptr{p} {}

    // friend declarations
    template<class, class>
    friend
    class list;

public:
    // traits
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using reference = value_type &;
    using pointer = value_type *;
    using difference_type = pointer_traits<pointer>::difference_type;

    // constructors
    inline list_const_iterator() noexcept : _ptr{nullptr} {}

    inline list_const_iterator(const list_iterator<T, Void_ptr> &p) noexcept : _ptr{p._ptr} {}

    // operator overloads
    inline reference operator*() const { return _ptr->_base_as_node()->_value; }

    inline pointer operator->() const { return std::addressof(_ptr->_base_as_node()->_value); }

    inline list_const_iterator &operator++() {
        _ptr = _ptr->_next;
        return *this;
    }

    inline list_const_iterator &operator++(int) {
        list_const_iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    inline list_const_iterator &operator--() {
        _ptr = _ptr->_prev;
        return *this;
    }

    inline list_const_iterator &operator--(int) {
        list_const_iterator tmp(*this);
        --(*this);
        return tmp;
    }

    friend
    inline bool operator==(const list_const_iterator &x, const list_const_iterator &y) { return x._ptr == y._ptr; }

    friend
    inline bool operator!=(const list_const_iterator &x, const list_const_iterator &y) { return !(x == y); }
};

// list class
// NOTE: default to using std::allocator is commented out in libc++
template<typename T, typename Allocator = allocator<T>>
class list {
public:
    // public traits
    using value_type = T;
    using allocator_type = Allocator;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = Allocator_traits::pointer;
    using const_pointer = Allocator_traits::const_pointer;
    using difference_type = Allocator_traits::difference_type;

    using Allocator_traits = std::allocator_traits<allocator_type>;
    using size_type = Allocator_traits::size_type;
    using void_pointer = Allocator_traits::void_pointer;

    using iterator = list_iterator<value_type, void_pointer>;
    using const_iterator = list_const_iterator<value_type, void_pointer>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using node_base = list_node_base<value_type, void_pointer>;
    using node = list_node<value_type, void_pointer>;
    // node allocator and node allocator traits
    using node_pointer = node::node_pointer;
    using node_const_pointer = node::node_pointer;
    using node_pointer_traits = list_node_pointer_traits<value_type, void_pointer>;
    using link_pointer = node_pointer_traits::link_pointer;
    using link_const_pointer = link_pointer;

private:
    // members
    size_type _size;
    node _end;

public:
    // constructors
    inline list() noexcept {}

    explicit list(size_type n);

    list(size_type n, const value_type &x);

    template<typename Input_iter>
    list(Input_iter first, Input_iter last,
         typename std::enable_if<std::__is_input_iterator<Input_iter>::value>::type * = 0);

    list(const list &c);

    inline list &operator=(const list &c);

    list(std::initializer_list<value_type> il);

    inline list(list &&c) noexcept;

    inline list &operator=(list &&c);

    inline list &operator=(std::initializer_list<value_type> il) {
        assign(il.begin(), il.end());
        return *this;
    }

    template<typename Input_iter>
    void assign(Input_iter first, Input_iter last,
         typename std::enable_if<std::__is_input_iterator<Input_iter>::value>::type * = 0);
};


#endif //LISTS_SIMPLIFIED_STD_LIST_H
