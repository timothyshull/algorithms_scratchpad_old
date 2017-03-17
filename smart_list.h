#ifndef LISTS_SMART_LIST_H
#define LISTS_SMART_LIST_H

#include <memory>
#include <limits>
#include <initializer_list>
#include <iterator>
#include <algorithm>
#include <type_traits>
#include <cstdio>
#include <cstdlib>

# define slassert(x, m) ((x) ? (void)0 : (std::fprintf(stderr, "%s\n", m), std::abort()))
using std::is_pointer;
using std::is_same;
using std::allocator;
using std::allocator_traits;
using std::is_nothrow_default_constructible;
using std::is_nothrow_move_assignable;
using std::true_type;
using std::false_type;
using std::__rebind_pointer;
using std::conditional;
using std::__rebind_alloc_helper;
using std::compressed_pair;
using std::integral_constant;
using std::__is_nothrow_swappable;
using std::__swap_allocator;
using std::__is_input_iterator;
using std::enable_if;
using std::is_nothrow_move_constructible;
using std::initializer_list;
using std::numeric_limits;
using std::move_iterator;
using std::unique_ptr;
using std::__allocator_destructor;
using std::__equal_to;
using std::less;


// Begin list definition

template<typename T>
struct List_node;

template<typename T>
struct list_node_pointer_traits {
    using node_pointer = std::unique_ptr<List_node<T>>;
    using link_pointer = node_pointer;

    using unowned_link_pointer = List_node<T> *;
};

template<typename T>
struct List_node {
    // members
    T value_;
    link_pointer next_;
    link_pointer prev_;

    // traits
    using Node_traits = list_node_pointer_traits<T>;
    using node_pointer = Node_traits::node_pointer;
    using link_pointer = Node_traits::link_pointer;
    using unowned_link_pointer = Node_traits::unowned_link_pointer;

    // constructors
    inline List_node() : next_{nullptr}, prev_{nullptr} {}
};

template<typename T>
class list;

template<typename T>
class list_const_iterator;

template<typename T>
class list_iterator {
    using Node_traits = list_node_pointer_traits<T>;
    using link_pointer = Node_traits::link_pointer;
    link_pointer ptr_;

    inline explicit list_iterator(link_pointer p) noexcept : ptr_{p} {}

    template<class, class>
    friend
    class list;

    template<class, class>
    friend
    class list_const_iterator;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using reference = value_type &;
    using pointer = value_type *;  // reconsider this
    using difference_type = typename std::pointer_traits<pointer>::difference_type;

    inline list_iterator() noexcept : ptr_{nullptr} {}

    inline reference operator*() const {
        return ptr_->value_;
    }

    inline pointer operator->() const {
        return std::pointer_traits<pointer>::pointer_to(ptr_->->value_);
    }

    inline list_iterator &operator++() {
        ptr_ = ptr_->next_;
        return *this;
    }

    inline list_iterator operator++(int) {
        list_iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    friend
    inline bool operator==(const list_iterator &x, const list_iterator &y) {
        return x.ptr_ == y.ptr_;
    }

    friend
    inline bool operator!=(const list_iterator &x, const list_iterator &y) { return !(x == y); }
};

template<typename T>
class list_const_iterator {
    using Node_traits = list_node_pointer_traits<T>;
    using link_pointer = typename Node_traits::link_pointer;
    link_pointer ptr_;

    inline explicit list_const_iterator(link_pointer p) noexcept : ptr_{p} {}

    template<class, class>
    friend
    class list;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using reference = const value_type &;
    using pointer = value_type *;
    using difference_type = typename std::pointer_traits<pointer>::difference_type;

    inline list_const_iterator() noexcept : ptr_(nullptr) {}

    inline list_const_iterator(const list_iterator<T> &p) noexcept : ptr_{p.ptr_} {}

    inline reference operator*() const {
        return ptr_->value_;
    }

    inline pointer operator->() const {
        return std::pointer_traits<pointer>::pointer_to(ptr_->value_);
    }

    inline list_const_iterator &operator++() {
        ptr_ = ptr_->next_;
        return *this;
    }

    inline list_const_iterator operator++(int) {
        list_const_iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    friend
    inline bool operator==(const list_const_iterator &x, const list_const_iterator &y) {
        return x.ptr_ == y.ptr_;
    }

    friend
    inline bool operator!=(const list_const_iterator &x, const list_const_iterator &y) {
        return !(x == y);
    }
};

template<typename T>
class list {
    // private traits
    using node = List_node<value_type>;
    using node_pointer = typename node::node_pointer;
    using node_const_pointer = typename node::node_pointer;
    using node_pointer_traits = list_node_pointer_traits<value_type>;
    using link_pointer = typename node_pointer_traits::link_pointer;
    using link_const_pointer = link_pointer;
    // private members
    node_pointer begin_;
    node_pointer end_;
    size_type size_;
public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = value_type const *;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;  // check on this because of the relationship with max_size
    using iterator = list_iterator<value_type>;
    using const_iterator = list_const_iterator<value_type>;

    inline list() {}

    explicit list(size_type n);

    list(size_type n, const value_type &x);

    template<class Input_iter>
    list(Input_iter f, Input_iter l, typename std::enable_if<__is_input_iterator<Input_iter>::value>::type * = 0);

    list(const list &c);

    inline list &operator=(const list &c);

    list(initializer_list<value_type> il);

    inline list &operator=(list &&c);

    inline list &operator=(initializer_list<value_type> __il) {
        assign(__il.begin(), __il.end());
        return *this;
    }

    ~list();

    template<class Input_iter>
    void
    assign(Input_iter f, Input_iter l, typename std::enable_if<__is_input_iterator<Input_iter>::value>::type * = 0);

    void assign(size_type n, const value_type &x);

    inline void assign(initializer_list<value_type> il) { assign(il.begin(), il.end()); }

    inline size_type size() const noexcept { return size_; }

    inline bool empty() const noexcept { return size_ == 0; } // first_ == nullptr

    inline size_type
    max_size() const noexcept { return static_cast<size_type>(numeric_limits<difference_type>::max()); }

    inline iterator begin() noexcept { return iterator{begin_}; }

    inline const_iterator begin() const noexcept { return const_iterator{begin_}; }

    inline iterator end() noexcept { return iterator{end_->next_}; }

    inline const_iterator end() const noexcept { return const_iterator{end_->next_}; }

    inline const_iterator cbegin() const noexcept { return const_iterator{begin_}; }

    inline const_iterator cend() const noexcept { return const_iterator{end_->next_}; }

    inline reference front() {
        slassert(!empty(), "list::front called on empty list");
        return begin_->value_;
    }

    inline const_reference front() const {
        slassert(!empty(), "list::front called on empty list");
        return begin_->value_;
    }

    inline reference back() {
        slassert(!empty(), "list::back called on empty list");
        return end_->value_;
    }

    inline const_reference back() const {
        slassert(!empty(), "list::back called on empty list");
        return end_->value_;
    }

    void push_front(value_type &&x);

    void push_back(value_type &&x);

    template<class... Args>
    reference emplace_front(Args &&... args);

    template<class... Args>
    reference emplace_back(Args &&... args);

    template<class... Args>
    iterator emplace(const_iterator p, Args &&... args);

    iterator insert(const_iterator p, value_type &&x);

    void push_front(const value_type &x);

    void push_back(const value_type &x);

    iterator insert(const_iterator p, const value_type &x);

    iterator insert(const_iterator p, size_type n, const value_type &x);

    template<class Input_iter>
    iterator
    insert(const_iterator p, Input_iter f, Input_iter l, typename std::enable_if<__is_input_iterator<Input_iter>::value>::type * = 0);

    inline iterator insert(const_iterator p, initializer_list<value_type> il) {
        return insert(p, il.begin(), il.end());
    }

    inline void swap(list &c) noexcept;

    inline void clear() noexcept;

    void pop_front();

    void pop_back();

    iterator erase(const_iterator __p);

    iterator erase(const_iterator f, const_iterator l);

    void resize(size_type __n);

    void resize(size_type __n, const value_type &x);

    void splice(const_iterator __p, list &c);

    inline void splice(const_iterator __p, list &&c) { splice(__p, c); }

    void splice(const_iterator __p, list &c, const_iterator __i);

    inline void splice(const_iterator __p, list &&c, const_iterator __i) { splice(__p, c, __i); }

    void splice(const_iterator __p, list &c, const_iterator f, const_iterator l);

    inline void splice(const_iterator __p, list &&c, const_iterator f, const_iterator l) {
        splice(__p, c, f, l);
    }

    void remove(const value_type &x);

    template<class _Pred>
    void remove_if(_Pred __pred);

    inline void unique();

    template<class BinaryPred>
    void unique(BinaryPred binary_pred);

    inline void merge(list &c);

    inline void merge(list &&c) { merge(c); }

    template<class Comp>
    void merge(list &c, Comp comp);

    template<class Comp>
    inline void merge(list &&c, Comp comp) { merge(c, comp); }

    inline void sort();

    template<class Comp>
    inline void sort(Comp comp);

    void reverse() noexcept;

    bool _invariants() const;

private:
    inline static void _unlink_nodes(link_pointer f, link_pointer l) noexcept;

    inline static void _link_nodes(link_pointer p, link_pointer f, link_pointer l);

    inline void _link_nodes_at_front(link_pointer f, link_pointer l);

    inline void _link_nodes_at_back(link_pointer f, link_pointer l);

    iterator _iterator(size_type n);

    template<class Comp>
    static iterator _sort(iterator f1, iterator e2, size_type __n, Comp &comp);

    void _move_assign(list &c, false_type);
};


// from base

// Unlink nodes [f, l]
template<typename T>
inline void list<T>::_unlink_nodes(link_pointer f, link_pointer l) noexcept {
    f->prev_->next_ = l->next_;
    l->next_->prev_ = f->prev_;
}

template<typename T>
list<T>::~list() {
    clear();
}

template<typename T>
void list<T>::clear() noexcept {
    if (!empty()) {
        link_pointer f = begin_;
        link_pointer l = end_;
        _unlink_nodes(f, l->prev_);
        size_ = 0;
        while (f != l) {
            node_pointer np = f;
            f = f->next_;
//            __node_alloc_traits::destroy(__na, std::addressof(__np->__value_));
//            __node_alloc_traits::deallocate(__na, __np, 1);

        }
    }
}

template<typename T>
void list<T>::swap(list &c) noexcept {
    using std::swap;
    swap(size_, c.size_);
    swap(begin_, c.begin_);
    if (size_ == 0) {
        begin_ = nullptr;
        end_ = nullptr;
//        end_.next_ = end_.prev_ = end_as_link();
    } else {
//        end_.prev_->next_ = end_.next_->prev_ = end_as_link();
    }
    if (c.size_ == 0) {
        c.begin_ = nullptr;
        c.end_ = nullptr;
//        c.end_.next_ = c.end_.prev_ = c.end_as_link();
    } else {
//        c.end_.prev_->next_ = c.end_.next_->prev_ = c.end_as_link();
    }
}

// end base


// Link in nodes [f, l] just prior to __p
template<typename T>
inline void list<T>::_link_nodes(link_pointer p, link_pointer f, link_pointer l) {
    p->prev_->next_ = f;
    f->prev_ = p->prev_;
    p->prev_ = l;
    l->next_ = p;
}

// Link in nodes [f, l] at the front of the list
template<typename T>
inline void list<T>::_link_nodes_at_front(link_pointer f, link_pointer l) {
    f->prev_ = end_as_link();
    l->next_ = end_.next_;
    l->next_->prev_ = l;
    end_.next_ = f;
}

// Link in nodes [f, l] at the front of the list
template<typename T>
inline void list<T>::_link_nodes_at_back(link_pointer f, link_pointer l) {
    l->next_ = end_as_link();
    f->prev_ = end_.prev_;
    f->prev_->next_ = f;
    end_.prev_ = l;
}

template<typename T>
inline
typename list<T>::iterator
list<T>::_iterator(size_type n) {
    return n <= size_ / 2 ? std::next(begin(), n)
                          : std::prev(end(), size_ - n);
}

template<typename T>
list<T>::list(size_type __n) {
    for (; __n > 0; --__n) {
        emplace_back();
    }
}

template<typename T>
list<T>::list(size_type __n, const value_type &x) {
    for (; __n > 0; --__n) {
        push_back(x);
    }
}

template<typename T>
list<T>::list(size_type __n, const value_type &x, const allocator_type &__a)
        : base(__a) {
    for (; __n > 0; --__n) {
        push_back(x);
    }
}

template<typename T>
template<class _InpIter>
list<T>::list(_InpIter f, _InpIter l,
              typename enable_if<__is_input_iterator<_InpIter>::value>::type *) {
    for (; f != l; ++f) {
        push_back(*f);
    }
}

template<typename T>
template<class _InpIter>
list<T>::list(_InpIter f, _InpIter l, const allocator_type &__a,
              typename enable_if<__is_input_iterator<_InpIter>::value>::type *)
        : base(__a) {
    for (; f != l; ++f) {
        push_back(*f);
    }
}

template<typename T>
list<T>::list(const list &c)
        : base(allocator_type(
        __node_alloc_traits::select_on_container_copy_construction(
                c.__node_alloc()))) {
    for (const_iterator __i = c.begin(), __e = c.end(); __i != __e; ++__i) {
        push_back(*__i);
    }
}

template<typename T>
list<T>::list(const list &c, const allocator_type &__a)
        : base(__a) {
    for (const_iterator __i = c.begin(), __e = c.end(); __i != __e; ++__i) {
        push_back(*__i);
    }
}

template<typename T>
list<T>::list(initializer_list<value_type> __il, const allocator_type &__a)
        : base(__a) {
    for (typename initializer_list<value_type>::const_iterator __i = __il.begin(),
                 __e = __il.end(); __i != __e; ++__i) {
                     push_back(*__i);
    }
}

template<typename T>
list<T>::list(initializer_list<value_type> __il) {
    for (typename initializer_list<value_type>::const_iterator __i = __il.begin(),
                 __e = __il.end(); __i != __e; ++__i) {
                     push_back(*__i);
    }
}

template<typename T>
inline
list<T> &
list<T>::operator=(const list &c) {
    if (this != &c) {
        copy_assign_alloc(c);
        assign(c.begin(), c.end());
    }
    return *this;
}

template<typename T>
inline
list<T>::list(list &&c)
noexcept(is_nothrow_move_constructible<__node_allocator>::value)
        : base(allocator_type(std::move(c.__node_alloc()))) {
    splice(end(), c);
}

template<typename T>
inline list<T> &list<T>::operator=(list &&c) {
    _move_assign(c, integral_constant<bool, __node_alloc_traits::propagate_on_container_move_assignment::value>());
    return *this;
}

template<typename T>
void list<T>::_move_assign(list &c, false_type) {
    if (__node_alloc() != c.__node_alloc()) {
        typedef move_iterator<iterator> _Ip;
        assign(_Ip(c.begin()), _Ip(c.end()));
    } else {
        __move_assign(c, true_type());
    }
}

template<typename T>
void list<T>::_move_assign(list &c, true_type)
noexcept(is_nothrow_move_assignable<__node_allocator>::value) {
    clear();
    __move_assign_alloc(c);
    splice(end(), c);
}

template<typename T>
template<class Input_iter>
void list<T>::assign(Input_iter f, Input_iter l, typename enable_if<__is_input_iterator<Input_iter>::value>::type *) {
    iterator __i = begin();
    iterator __e = end();
    for (; f != l && __i != __e; ++f, ++__i) {
        *__i = *f;
    }
    if (__i == __e) {
        insert(__e, f, l);
    } else {
        erase(__i, __e);
    }
}

template<typename T>
void list<T>::assign(size_type __n, const value_type &x) {
    iterator __i = begin();
    iterator __e = end();
    for (; __n > 0 && __i != __e; --__n, ++__i) {
        *__i = x;
    }
    if (__i == __e) {
        insert(__e, __n, x);
    } else {
        erase(__i, __e);
    }
}

template<typename T>
typename list<T>::iterator
list<T>::insert(const_iterator __p, const value_type &x) {
    __node_allocator &__na = __node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __hold->prev_ = 0;
    __node_alloc_traits::construct(__na, std::addressof(__hold->__value_), x);
    _link_nodes(__p.ptr_, __hold->__as_link(), __hold->__as_link());
    ++size_;
    return iterator(__hold.release()->__as_link());
}

template<typename T>
typename list<T>::iterator
list<T>::insert(const_iterator __p, size_type __n, const value_type &x) {
    iterator __r(__p.ptr_);
    if (__n > 0) {
        size_type ds = 0;
        __node_allocator &__na = __node_alloc();
        typedef __allocator_destructor<__node_allocator> _Dp;
        unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        __hold->prev_ = 0;
        __node_alloc_traits::construct(__na, std::addressof(__hold->__value_), x);
        ++ds;
        __r = iterator(__hold->__as_link());
        __hold.release();
        iterator __e = __r;
        try {
            for (--__n; __n != 0; --__n, ++__e, ++ds) {
                __hold.reset(__node_alloc_traits::allocate(__na, 1));
                __node_alloc_traits::construct(__na, std::addressof(__hold->__value_), x);
                __e.ptr_->next_ = __hold->__as_link();
                __hold->prev_ = __e.ptr_;
                __hold.release();
            }
        }
        catch (...) {
            while (true) {
                __node_alloc_traits::destroy(__na, std::addressof(*__e));
                link_pointer __prev = __e.ptr_->prev_;
                __node_alloc_traits::deallocate(__na, __e.ptr_->__as_node(), 1);
                if (__prev == 0) {
                    break;
                }
                __e = iterator(__prev);
            }
            throw;
        }
        _link_nodes(__p.ptr_, __r.ptr_, __e.ptr_);
        size_ += ds;
    }
    return __r;
}

template<typename T>
template<class _InpIter>
typename list<T>::iterator
list<T>::insert(const_iterator __p, _InpIter f, _InpIter l,
                typename enable_if<__is_input_iterator<_InpIter>::value>::type *) {
    iterator __r(__p.ptr_);
    if (f != l) {
        size_type ds = 0;
        __node_allocator &__na = __node_alloc();
        typedef __allocator_destructor<__node_allocator> _Dp;
        unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        __hold->prev_ = 0;
        __node_alloc_traits::construct(__na, std::addressof(__hold->__value_), *f);
        ++ds;
        __r = iterator(__hold.get()->__as_link());
        __hold.release();
        iterator __e = __r;
        try {
            for (++f; f != l; ++f, (void) ++__e, (void) ++ds) {
                __hold.reset(__node_alloc_traits::allocate(__na, 1));
                __node_alloc_traits::construct(__na, std::addressof(__hold->__value_), *f);
                __e.ptr_->next_ = __hold.get()->__as_link();
                __hold->prev_ = __e.ptr_;
                __hold.release();
            }
        }
        catch (...) {
            while (true) {
                __node_alloc_traits::destroy(__na, std::addressof(*__e));
                link_pointer __prev = __e.ptr_->prev_;
                __node_alloc_traits::deallocate(__na, __e.ptr_->__as_node(), 1);
                if (__prev == 0) {
                    break;
                }
                __e = iterator(__prev);
            }
            throw;
        }
        _link_nodes(__p.ptr_, __r.ptr_, __e.ptr_);
        size_ += ds;
    }
    return __r;
}

template<typename T>
void
list<T>::push_front(const value_type &x) {
    __node_allocator &__na = __node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __node_alloc_traits::construct(__na, std::addressof(__hold->__value_), x);
    link_pointer __nl = __hold->__as_link();
    _link_nodes_at_front(__nl, __nl);
    ++size_;
    __hold.release();
}

template<typename T>
void
list<T>::push_back(const value_type &x) {
    __node_allocator &__na = __node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __node_alloc_traits::construct(__na, std::addressof(__hold->__value_), x);
    _link_nodes_at_back(__hold.get()->__as_link(), __hold.get()->__as_link());
    ++size_;
    __hold.release();
}

template<typename T>
void
list<T>::push_front(value_type &&x) {
    __node_allocator &__na = __node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __node_alloc_traits::construct(__na, std::addressof(__hold->__value_), std::move(x));
    _link_nodes_at_front(__hold.get()->__as_link(), __hold.get()->__as_link());
    ++size_;
    __hold.release();
}

template<typename T>
void
list<T>::push_back(value_type &&x) {
    __node_allocator &__na = __node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __node_alloc_traits::construct(__na, std::addressof(__hold->__value_), std::move(x));
    _link_nodes_at_back(__hold.get()->__as_link(), __hold.get()->__as_link());
    ++size_;
    __hold.release();
}

template<typename T>
template<class... _Args>
typename list<T>::reference
list<T>::emplace_front(_Args &&... __args) {
    __node_allocator &__na = __node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __node_alloc_traits::construct(__na, std::addressof(__hold->__value_), std::forward<_Args>(__args)...);
    _link_nodes_at_front(__hold.get()->__as_link(), __hold.get()->__as_link());
    ++size_;
    return __hold.release()->__value_;
}

template<typename T>
template<class... _Args>
typename list<T>::reference
list<T>::emplace_back(_Args &&... __args) {
    __node_allocator &__na = __node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __node_alloc_traits::construct(__na, std::addressof(__hold->__value_), std::forward<_Args>(__args)...);
    link_pointer __nl = __hold->__as_link();
    _link_nodes_at_back(__nl, __nl);
    ++size_;
    return __hold.release()->__value_;
}

template<typename T>
template<class... _Args>
typename list<T>::iterator
list<T>::emplace(const_iterator __p, _Args &&... __args) {
    __node_allocator &__na = __node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __hold->prev_ = 0;
    __node_alloc_traits::construct(__na, std::addressof(__hold->__value_), std::forward<_Args>(__args)...);
    link_pointer __nl = __hold.get()->__as_link();
    _link_nodes(__p.ptr_, __nl, __nl);
    ++size_;
    __hold.release();
    return iterator(__nl);
}

template<typename T>
typename list<T>::iterator
list<T>::insert(const_iterator __p, value_type &&x) {
    __node_allocator &__na = __node_alloc();
    typedef __allocator_destructor<__node_allocator> _Dp;
    unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
    __hold->prev_ = 0;
    __node_alloc_traits::construct(__na, std::addressof(__hold->__value_), std::move(x));
    link_pointer __nl = __hold->__as_link();
    _link_nodes(__p.ptr_, __nl, __nl);
    ++size_;
    __hold.release();
    return iterator(__nl);
}

template<typename T>
void
list<T>::pop_front() {
    slassert(!empty(), "list::pop_front() called with empty list");
    __node_allocator &__na = __node_alloc();
    link_pointer __n = end_.next_;
    _unlink_nodes(__n, __n);
    --size_;
    __node_pointer __np = __n->__as_node();
    __node_alloc_traits::destroy(__na, std::addressof(__np->__value_));
    __node_alloc_traits::deallocate(__na, __np, 1);
}

template<typename T>
void
list<T>::pop_back() {
    slassert(!empty(), "list::pop_back() called with empty list");
    __node_allocator &__na = __node_alloc();
    link_pointer __n = end_.prev_;
    _unlink_nodes(__n, __n);
    --size_;
    __node_pointer __np = __n->__as_node();
    __node_alloc_traits::destroy(__na, std::addressof(__np->__value_));
    __node_alloc_traits::deallocate(__na, __np, 1);
}

template<typename T>
typename list<T>::iterator
list<T>::erase(const_iterator __p) {
    slassert(__p != end(),
             "list::erase(iterator) called with a non-dereferenceable iterator");
    __node_allocator &__na = __node_alloc();
    link_pointer __n = __p.ptr_;
    link_pointer __r = __n->next_;
    _unlink_nodes(__n, __n);
    --size_;
    __node_pointer __np = __n->__as_node();
    __node_alloc_traits::destroy(__na, std::addressof(__np->__value_));
    __node_alloc_traits::deallocate(__na, __np, 1);
    return iterator(__r);
}

template<typename T>
typename list<T>::iterator
list<T>::erase(const_iterator f, const_iterator l) {
    if (f != l) {
        __node_allocator &__na = __node_alloc();
        _unlink_nodes(f.ptr_, l.ptr_->prev_);
        while (f != l) {
            link_pointer __n = f.ptr_;
            ++f;
            --size_;
            __node_pointer __np = __n->__as_node();
            __node_alloc_traits::destroy(__na, std::addressof(__np->__value_));
            __node_alloc_traits::deallocate(__na, __np, 1);
        }
    }
    return iterator(l.ptr_);
}

template<typename T>
void
list<T>::resize(size_type __n) {
    if (__n < size_) {
        erase(__iterator(__n), end());
    } else if (__n > size_) {
        __n -= size_;
        size_type ds = 0;
        __node_allocator &__na = __node_alloc();
        typedef __allocator_destructor<__node_allocator> _Dp;
        unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        __hold->prev_ = 0;
        __node_alloc_traits::construct(__na, std::addressof(__hold->__value_));
        ++ds;
        iterator __r = iterator(__hold.release()->__as_link());
        iterator __e = __r;
        try {
            for (--__n; __n != 0; --__n, ++__e, ++ds) {
                __hold.reset(__node_alloc_traits::allocate(__na, 1));
                __node_alloc_traits::construct(__na, std::addressof(__hold->__value_));
                __e.ptr_->next_ = __hold.get()->__as_link();
                __hold->prev_ = __e.ptr_;
                __hold.release();
            }
        }
        catch (...) {
            while (true) {
                __node_alloc_traits::destroy(__na, std::addressof(*__e));
                link_pointer __prev = __e.ptr_->prev_;
                __node_alloc_traits::deallocate(__na, __e.ptr_->__as_node(), 1);
                if (__prev == 0) {
                    break;
                }
                __e = iterator(__prev);
            }
            throw;
        }
        _link_nodes_at_back(__r.ptr_, __e.ptr_);
        size_ += ds;
    }
}

template<typename T>
void
list<T>::resize(size_type __n, const value_type &x) {
    if (__n < size_) {
        erase(__iterator(__n), end());
    } else if (__n > size_) {
        __n -= size_;
        size_type ds = 0;
        __node_allocator &__na = __node_alloc();
        typedef __allocator_destructor<__node_allocator> _Dp;
        unique_ptr<__node, _Dp> __hold(__node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        __hold->prev_ = 0;
        __node_alloc_traits::construct(__na, std::addressof(__hold->__value_), x);
        ++ds;
        link_pointer __nl = __hold.release()->__as_link();
        iterator __r = iterator(__nl);
        iterator __e = __r;
        try {
            for (--__n; __n != 0; --__n, ++__e, ++ds) {
                __hold.reset(__node_alloc_traits::allocate(__na, 1));
                __node_alloc_traits::construct(__na, std::addressof(__hold->__value_), x);
                __e.ptr_->next_ = __hold.get()->__as_link();
                __hold->prev_ = __e.ptr_;
                __hold.release();
            }
        }
        catch (...) {
            while (true) {
                __node_alloc_traits::destroy(__na, std::addressof(*__e));
                link_pointer __prev = __e.ptr_->prev_;
                __node_alloc_traits::deallocate(__na, __e.ptr_->__as_node(), 1);
                if (__prev == 0) {
                    break;
                }
                __e = iterator(__prev);
            }
            throw;
        }
        _link_nodes(end_as_link(), __r.ptr_, __e.ptr_);
        size_ += ds;
    }
}

template<typename T>
void
list<T>::splice(const_iterator __p, list &c) {
    slassert(this != &c, "list::splice(iterator, list) called with this == &list");
    if (!c.empty()) {
        link_pointer f = c.end_.next_;
        link_pointer l = c.end_.prev_;
        _unlink_nodes(f, l);
        _link_nodes(__p.ptr_, f, l);
        size_ += c.size_;
        c.size_ = 0;
    }
}

template<typename T>
void
list<T>::splice(const_iterator __p, list &c, const_iterator __i) {
    if (__p.ptr_ != __i.ptr_ && __p.ptr_ != __i.ptr_->next_) {
        link_pointer f = __i.ptr_;
        _unlink_nodes(f, f);
        _link_nodes(__p.ptr_, f, f);
        --c.size_;
        ++size_;
    }
}

template<typename T>
void
list<T>::splice(const_iterator __p, list &c, const_iterator f, const_iterator l) {
    if (f != l) {
        if (this != &c) {
            size_type __s = static_cast<size_type>(std::distance(f, l));
            c.size_ -= __s;
            size_ += __s;
        }
        link_pointer first = f.ptr_;
        --l;
        link_pointer last = l.ptr_;
        _unlink_nodes(first, last);
        _link_nodes(__p.ptr_, first, last);
    }
}

template<typename T>
void
list<T>::remove(const value_type &x) {
    list<T> __deleted_nodes; // collect the nodes we're removing
    for (const_iterator __i = begin(), __e = end(); __i != __e;) {
        if (*__i == x) {
            const_iterator __j = std::next(__i);
            for (; __j != __e && *__j == x; ++__j) {}
            __deleted_nodes.splice(__deleted_nodes.end(), *this, __i, __j);
            __i = __j;
            if (__i != __e) {
                ++__i;
            }
        } else {
            ++__i;
        }
    }
}

template<typename T>
template<class _Pred>
void
list<T>::remove_if(_Pred __pred) {
    for (iterator __i = begin(), __e = end(); __i != __e;) {
        if (__pred(*__i)) {
            iterator __j = std::next(__i);
            for (; __j != __e && __pred(*__j); ++__j) {}
            __i = erase(__i, __j);
            if (__i != __e) {
                ++__i;
            }
        } else {
            ++__i;
        }
    }
}

template<typename T>
inline
void
list<T>::unique() {
    unique(__equal_to<value_type>());
}

template<typename T>
template<class BinaryPred>
void
list<T>::unique(BinaryPred binary_pred) {
    for (iterator i = begin(), e = end(); i != e;) {
        iterator j = std::next(i);
        for (; j != e && binary_pred(*i, *j); ++j) {}
        if (++i != j) {
            i = erase(i, j);
        }
    }
}

template<typename T>
inline
void
list<T>::merge(list &c) {
    merge(c, less<value_type>());
}

template<typename T>
template<class Comp>
void
list<T>::merge(list &c, Comp comp) {
    if (this != &c) {
        iterator f1 = begin();
        iterator e1 = end();
        iterator f2 = c.begin();
        iterator e2 = c.end();
        while (f1 != e1 && f2 != e2) {
            if (comp(*f2, *f1)) {
                size_type ds = 1;
                iterator m2 = std::next(f2);
                for (; m2 != e2 && comp(*m2, *f1); ++m2, ++ds) {}
                size_ += ds;
                c.size_ -= ds;
                link_pointer f = f2.ptr_;
                link_pointer l = m2.ptr_->prev_;
                f2 = m2;
                _unlink_nodes(f, l);
                m2 = std::next(f1);
                _link_nodes(f1.ptr_, f, l);
                f1 = m2;
            } else {
                ++f1;
            }
        }
        splice(e1, c);
    }
}

template<typename T>
inline
void
list<T>::sort() {
    sort(less<value_type>());
}

template<typename T>
template<class Comp>
inline
void
list<T>::sort(Comp comp) {
    _sort(begin(), end(), size_, comp);
}

template<typename T>
template<class Comp>
typename list<T>::iterator
list<T>::_sort(iterator f1, iterator e2, size_type n, Comp &comp) {
    switch (n) {
        case 0:
        case 1:
            return f1;
        case 2:
            if (comp(*--e2, *f1)) {
                link_pointer f = e2.ptr_;
                _unlink_nodes(f, f);
                _link_nodes(f1.ptr_, f, f);
                return e2;
            }
            return f1;
    }
    size_type n2 = n / 2;
    iterator e1 = std::next(f1, n2);
    iterator r = f1 = _sort(f1, e1, n2, comp);
    iterator f2 = e1 = _sort(e1, e2, n - n2, comp);
    if (comp(*f2, *f1)) {
        iterator m2 = std::next(f2);
        for (; m2 != e2 && comp(*m2, *f1); ++m2) {}
        link_pointer f = f2.ptr_;
        link_pointer l = m2.ptr_->prev_;
        r = f2;
        e1 = f2 = m2;
        _unlink_nodes(f, l);
        m2 = std::next(f1);
        _link_nodes(f1.ptr_, f, l);
        f1 = m2;
    } else {
        ++f1;
    }
    while (f1 != e1 && f2 != e2) {
        if (comp(*f2, *f1)) {
            iterator m2 = std::next(f2);
            for (; m2 != e2 && comp(*m2, *f1); ++m2) {}
            link_pointer f = f2.ptr_;
            link_pointer l = m2.ptr_->prev_;
            if (e1 == f2) {
                e1 = m2;
            }
            f2 = m2;
            _unlink_nodes(f, l);
            m2 = std::next(f1);
            _link_nodes(f1.ptr_, f, l);
            f1 = m2;
        } else {
            ++f1;
        }
    }
    return r;
}

template<typename T>
void list<T>::reverse() noexcept {
    if (size_ > 1) {
        iterator e = end();
        for (iterator i = begin(); i.ptr_ != e.ptr_;) {
            std::swap(i.ptr_->prev_, i.ptr_->next_);
            i.ptr_ = i.ptr_->prev_;
        }
        std::swap(e.ptr_->prev_, e.ptr_->next_);
    }
}

template<typename T>
bool list<T>::_invariants() const {
    return size() == std::distance(begin(), end());
}

template<typename T>
inline bool operator==(const list<T> &x, const list<T> &y) {
    return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
}

template<typename T>
inline bool operator<(const list<T> &x, const list<T> &y) {
    return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template<typename T>
inline bool operator!=(const list<T> &x, const list<T> &y) {
    return !(x == y);
}

template<typename T>
inline bool operator>(const list<T> &x, const list<T> &y) {
    return y < x;
}

template<typename T>
inline bool operator>=(const list<T> &x, const list<T> &y) {
    return !(x < y);
}

template<typename T>
inline bool operator<=(const list<T> &x, const list<T> &y) {
    return !(y < x);
}

template<typename T>
inline void swap(list<T> &x, list<T> &y) noexcept(noexcept(x.swap(y))) {
    x.swap(y);
}

#endif //LISTS_SMART_LIST_H
