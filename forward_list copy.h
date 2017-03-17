#ifndef CUSTOM_ALGORITHMS_FORWARD_LIST_H
#define CUSTOM_ALGORITHMS_FORWARD_LIST_H

#include <initializer_list>
#include <memory>
#include <limits>
#include <iterator>
#include <algorithm>

#include <boost/compressed_pair.hpp>
#include <functional>

using std::pointer_traits;
using std::allocator;
using std::forward_iterator_tag;
using std::remove_const;
using std::allocator_traits;
using std::is_nothrow_default_constructible;
using std::is_nothrow_move_constructible;
using std::integral_constant;
using std::is_nothrow_move_assignable;
using std::false_type;
using std::true_type;
using std::initializer_list;
using std::numeric_limits;
using std::move_iterator;
using std::unique_ptr;
using std::input_iterator_tag;
using std::enable_if;
using std::equal_to;
using std::less;

using boost::compressed_pair;

// helpers
template<class Traits, class T>
struct rebind_alloc_helper {
    using type = typename Traits::template rebind_alloc<T>::other;
};

struct nat {
    nat() = delete;

    nat(const nat &) = delete;

    nat &operator=(const nat &) = delete;

    ~nat() = delete;
};

template<class T>
struct swappable {
    using type = decltype(std::swap(std::declval<T &>(), std::declval<T &>()));
    static const bool value = !std::is_same<type, nat>::value;
};

template<class T>
struct is_swappable : public integral_constant<bool, swappable<T>::value> {
};

template<bool, class T>
struct is_nothrow_swappable_imp
        : public integral_constant<bool, noexcept(std::swap(std::declval<T &>(), std::declval<T &>()))> {
};

template<class T>
struct is_nothrow_swappable_imp<false, T> : public false_type {
};

template<class T>
struct is_nothrow_swappable : public is_nothrow_swappable_imp<is_swappable<T>::value, T> {
};

template<class T, class Up>
struct has_iterator_category_convertible_to<T, Up, false> : public false_type {
};

template<class T>
struct is_input_iterator : public has_iterator_category_convertible_to<T, input_iterator_tag> {
};

template<class Allocator>
class allocator_destructor {
    using alloc_traits = allocator_traits<Allocator>;
public:
    using pointer = typename alloc_traits::pointer;
    using size_type = typename alloc_traits::size_type;
private:
    Allocator &alloc_;
    size_type sz_;
public:
    allocator_destructor(Allocator &a, size_type s) noexcept : alloc_(a), sz_(s) {}

    void operator()(pointer p) noexcept { alloc_traits::deallocate(alloc_, p, sz_); }
};


// code
template<class T, class VoidPtr>
struct forward_list_node;

template<class NodePtr>
struct forward_begin_node {
    typedef NodePtr pointer;

    pointer next_;

    forward_begin_node() : next_(nullptr) {}
};

template<class T, class VoidPtr>
struct begin_node_of {
    using type =
    forward_begin_node<typename pointer_traits<VoidPtr>::template rebind<forward_list_node<T, VoidPtr> >::other>;
};

template<class T, class VoidPtr>
struct forward_list_node : public begin_node_of<T, VoidPtr>::type {
    using value_type = T;

    value_type value_;
};

template<class T, class Allocator = allocator<T> >
class forward_list;

template<class NodeConstPtr>
class forward_list_const_iterator;

template<class NodePtr>
class forward_list_iterator {
    using node_pointer = NodePtr;

    node_pointer ptr_;

    explicit forward_list_iterator(node_pointer p) noexcept : ptr_(p) {}

    template<class, class> friend
    class forward_list;

    template<class> friend
    class forward_list_const_iterator;

public:
    using iterator_category = forward_iterator_tag;
    using value_type = typename pointer_traits<node_pointer>::element_type::value_type;
    using reference = value_type &;
    using difference_type = typename pointer_traits<node_pointer>::difference_type;
    using pointer = typename pointer_traits<node_pointer>::template rebind<value_type>::other;

    forward_list_iterator() noexcept : ptr_(nullptr) {}

    reference operator*() const { return ptr_->value_; }

    pointer operator->() const { return pointer_traits<pointer>::pointer_to(ptr_->value_); }

    forward_list_iterator &operator++() {
        ptr_ = ptr_->next_;
        return *this;
    }

    forward_list_iterator operator++(int) {
        forward_list_iterator t(*this);
        ++(*this);
        return t;
    }

    friend
    bool operator==(const forward_list_iterator &x, const forward_list_iterator &y) { return x.ptr_ == y.ptr_; }

    friend
    bool operator!=(const forward_list_iterator &x, const forward_list_iterator &y) { return !(x == y); }
};

template<class NodeConstPtr>
class forward_list_const_iterator {
    using node_const_pointer = NodeConstPtr;
    using node = typename remove_const<typename pointer_traits<node_const_pointer>::element_type>::type;
    using node_pointer = typename pointer_traits<node_const_pointer>::template rebind<node>::other;

    node_const_pointer ptr_;

    explicit forward_list_const_iterator(node_const_pointer __p) noexcept : ptr_(__p) {}

    template<class, class>
    friend
    class forward_list;

public:
    using iterator_category = forward_iterator_tag;
    using value_type = typename node::value_type;
    using reference = const value_type &;
    using difference_type = typename pointer_traits<node_const_pointer>::difference_type;
    using pointer = typename pointer_traits<node_const_pointer>::template rebind<const value_type>::other;

    forward_list_const_iterator() noexcept : ptr_(nullptr) {}

    forward_list_const_iterator(forward_list_iterator<node_pointer> __p) noexcept : ptr_(__p.ptr_) {}

    reference operator*() const { return ptr_->value_; }

    pointer operator->() const { return pointer_traits<pointer>::pointer_to(ptr_->value_); }

    forward_list_const_iterator &operator++() {
        ptr_ = ptr_->next_;
        return *this;
    }

    forward_list_const_iterator operator++(int) {
        forward_list_const_iterator t(*this);
        ++(*this);
        return t;
    }

    friend
    bool operator==(const forward_list_const_iterator &x,
                    const forward_list_const_iterator &y) { return x.ptr_ == y.ptr_; }

    friend
    bool operator!=(const forward_list_const_iterator &x,
                    const forward_list_const_iterator &y) { return !(x == y); }
};

template<class T, class Allocator>
class forward_list_base {
protected:
    using value_type = T;
    using allocator_type = Allocator;
    using void_pointer = typename allocator_traits<allocator_type>::void_pointer;
    using node = forward_list_node<value_type, void_pointer>;
    using begin_node = typename begin_node_of<value_type, void_pointer>::type;
    using node_allocator = typename rebind_alloc_helper<allocator_traits<allocator_type>, node>::type;
    using node_traits = allocator_traits<node_allocator>;
    using node_pointer = typename node_traits::pointer;
    using node_const_pointer = typename node_traits::pointer;
    using begin_node_allocator = typename rebind_alloc_helper<allocator_traits<allocator_type>, begin_node>::type;
    using begin_node_pointer = typename allocator_traits<begin_node_allocator>::pointer;
    using iterator = forward_list_iterator<node_pointer>;
    using const_iterator = forward_list_const_iterator<node_pointer>;

    compressed_pair<begin_node, node_allocator> before_begin_;

    node_pointer before_begin() noexcept {
        return static_cast<node_pointer>(pointer_traits<begin_node_pointer>::
        pointer_to(before_begin_.first()));
    }

    node_const_pointer before_begin() const noexcept {
        return static_cast<node_const_pointer>(pointer_traits<begin_node_pointer>::
        pointer_to(const_cast<begin_node &>(before_begin_.first())));
    }

    node_allocator &alloc() noexcept { return before_begin_.second(); }

    const node_allocator &__alloc() const noexcept { return before_begin_.second(); }

    forward_list_base() noexcept(is_nothrow_default_constructible<node_allocator>::value) : before_begin_(
            begin_node()) {}

    forward_list_base(const allocator_type &__a) : before_begin_(begin_node(), node_allocator(__a)) {}

public:
    forward_list_base(forward_list_base &&x) noexcept(is_nothrow_move_constructible<node_allocator>::value);

    forward_list_base(forward_list_base &&x, const allocator_type &__a);

private:
    forward_list_base(const forward_list_base &);

    forward_list_base &operator=(const forward_list_base &);

public:
    ~forward_list_base();

protected:

    void __copy_assign_alloc(const forward_list_base &x) {
        __copy_assign_alloc(x, integral_constant<bool,
                node_traits::propagate_on_container_copy_assignment::value>());
    }


    void __move_assign_alloc(forward_list_base &x) noexcept(
    !node_traits::propagate_on_container_move_assignment::value ||
    is_nothrow_move_assignable<node_allocator>::value) {
        __move_assign_alloc(x, integral_constant<bool,
                node_traits::propagate_on_container_move_assignment::value>());
    }

public:
    void swap(forward_list_base &x) noexcept(!node_traits::propagate_on_container_move_assignment::value ||
                                             is_nothrow_swappable<node_allocator>::value);

protected:
    virtual void clear() noexcept;

private:

    void __copy_assign_alloc(const forward_list_base &, false_type) {}

    void __copy_assign_alloc(const forward_list_base &x, true_type) {
        if (alloc() != x.__alloc())
            clear();
        alloc() = x.__alloc();
    }


    void __move_assign_alloc(forward_list_base &x, false_type) noexcept {}

    void
    __move_assign_alloc(forward_list_base &x, true_type) noexcept(is_nothrow_move_assignable<node_allocator>::value) {
        alloc() = std::move(x.alloc());
    }
};

template<class T, class Allocator>
inline
forward_list_base<T, Allocator>::forward_list_base(
        forward_list_base &&x) noexcept(is_nothrow_move_constructible<node_allocator>::value) : before_begin_(
        std::move(x.before_begin_)) {
    x.before_begin()->next_ = nullptr;
}

template<class T, class Allocator>
inline
forward_list_base<T, Allocator>::forward_list_base(forward_list_base &&x, const allocator_type &__a)
        : before_begin_(begin_node(), node_allocator(__a)) {
    if (alloc() == x.alloc()) {
        before_begin()->next_ = x.before_begin()->next_;
        x.before_begin()->next_ = nullptr;
    }
}

template<class T, class Allocator>
forward_list_base<T, Allocator>::~forward_list_base() {
    clear();
}

template<class T, class Allocator>
inline
void
forward_list_base<T, Allocator>::swap(forward_list_base &x) noexcept(
!node_traits::propagate_on_container_move_assignment::value ||
is_nothrow_swappable<node_allocator>::value) {
    __swap_allocator(alloc(), x.alloc(),
                     integral_constant<bool, node_traits::propagate_on_container_swap::value>());
    using std::swap;
    swap(before_begin()->next_, x.before_begin()->next_

    );
}

template<class T, class Allocator>
void
forward_list_base<T, Allocator>::clear() noexcept {
    node_allocator &a = alloc();
    for (node_pointer p = before_begin()->next_; p != nullptr;) {
        node_pointer next = p->next_;
        node_traits::destroy(a, std::addressof(p->value_));
        node_traits::deallocate(a, p, 1);
        p = next;
    }
    before_begin()->next_ = nullptr;
}

template<class T, class Allocator>
class forward_list : private forward_list_base<T, Allocator> {
    using base = forward_list_base<T, Allocator>;
    using node_allocator = typename base::node_allocator;
    using node = typename base::node;
    using node_traits = typename base::node_traits;
    using node_pointer = typename base::node_pointer;

public:
    using value_type = T;
    using allocator_type = Allocator;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = typename allocator_traits<allocator_type>::pointer;
    using const_pointer = typename allocator_traits<allocator_type>::const_pointer;
    using size_type = typename allocator_traits<allocator_type>::size_type;
    using difference_type = typename allocator_traits<allocator_type>::difference_type;
    using iterator = typename base::iterator;
    using const_iterator = typename base::const_iterator;

    forward_list() noexcept(is_nothrow_default_constructible<node_allocator>::value) {} // = default;

    explicit forward_list(const allocator_type &a);

    explicit forward_list(size_type n);

    explicit forward_list(size_type n, const allocator_type &a);

    forward_list(size_type n, const value_type &a);

    forward_list(size_type n, const value_type &v, const allocator_type &a);

    template<class InputIterator>
    forward_list(InputIterator f, InputIterator l, std::iterator_traits<InputIterator>::value_type * = nullptr);

    template<class InputIterator>
    forward_list(InputIterator f, InputIterator l, const allocator_type &__a,
                 std::iterator_traits<InputIterator>::value_type * = nullptr);

    forward_list(const forward_list &x);

    forward_list(const forward_list &x, const allocator_type &a);

    forward_list(forward_list &&x) noexcept(is_nothrow_move_constructible<base>::value) : base(std::move(x)) {}

    forward_list(forward_list &&x, const allocator_type &a);

    forward_list(initializer_list<value_type> __il);

    forward_list(initializer_list<value_type> __il, const allocator_type &__a);

    // ~forward_list() = default;

    forward_list &operator=(const forward_list &x);

    forward_list &operator=(forward_list &&x) noexcept(node_traits::propagate_on_container_move_assignment::value &&
                                                       is_nothrow_move_assignable<allocator_type>::value);

    forward_list &operator=(initializer_list<value_type> il);

    template<class InputIterator>
//    typename enable_if<is_input_iterator<InputIterator>::value, void>::type
    void assign(InputIterator f, InputIterator l);

    void assign(size_type n, const value_type &v);

    void assign(initializer_list<value_type> il);

    allocator_type get_allocator() const noexcept { return allocator_type(base::__alloc()); }

    iterator begin() noexcept { return iterator(base::before_begin()->next_); }

    const_iterator begin() const noexcept { return const_iterator(base::before_begin()->next_); }

    iterator end() noexcept { return iterator(nullptr); }

    const_iterator end() const noexcept { return const_iterator(nullptr); }

    const_iterator cbegin() const noexcept { return const_iterator(base::before_begin()->next_); }

    const_iterator cend() const noexcept { return const_iterator(nullptr); }

    iterator before_begin() noexcept { return iterator(base::before_begin()); }

    const_iterator before_begin() const noexcept { return const_iterator(base::before_begin()); }

    const_iterator cbefore_begin() const noexcept { return const_iterator(base::before_begin()); }

    bool empty() const noexcept { return base::before_begin()->next_ == nullptr; }

    size_type max_size() const noexcept { return numeric_limits<size_type>::max(); }

    reference front() { return base::before_begin()->next_->value_; }

    const_reference front() const { return base::before_begin()->next_->value_; }

    template<class... _Args>
    void emplace_front(_Args &&... args);

    void push_front(value_type &&v);

    void push_front(const value_type &__v);

    void pop_front();

    template<class... _Args>
    iterator emplace_after(const_iterator p, _Args &&... __args);

    iterator insert_after(const_iterator __p, value_type &&__v);

    iterator insert_after(const_iterator __p, const value_type &__v);

    iterator insert_after(const_iterator __p, size_type __n, const value_type &__v);

    template<class InputIterator>
    typename std::iterator_traits<InputIterator>::value_type
    insert_after(const_iterator __p, InputIterator __f, InputIterator __l);

    iterator insert_after(const_iterator __p, initializer_list<value_type> __il) {
        return insert_after(__p, __il.begin(), __il.end());
    }

    iterator erase_after(const_iterator __p);

    iterator erase_after(const_iterator __f, const_iterator __l);

    void swap(forward_list &x) noexcept(!node_traits::propagate_on_container_swap::value ||
                                        is_nothrow_swappable<node_allocator>::value) { base::swap(x); }

    void resize(size_type __n);

    void resize(size_type __n, const value_type &__v);

    void clear() noexcept { base::clear(); }

    void splice_after(const_iterator __p, forward_list &&x);

    void splice_after(const_iterator __p, forward_list &&x, const_iterator __i);

    void splice_after(const_iterator __p, forward_list &&x,
                      const_iterator __f, const_iterator __l);

    void splice_after(const_iterator __p, forward_list &x);

    void splice_after(const_iterator __p, forward_list &x, const_iterator __i);

    void splice_after(const_iterator __p, forward_list &x,
                      const_iterator __f, const_iterator __l);

    void remove(const value_type &__v);

    template<class _Predicate>
    void remove_if(_Predicate __pred);

    void unique() { unique(equal_to<value_type>()); }

    template<class _BinaryPredicate>
    void unique(_BinaryPredicate __binary_pred);

    void merge(forward_list &&x) { merge(x, less<value_type>()); }

    template<class _Compare>

    void merge(forward_list &&x, _Compare __comp) { merge(x, std::move(__comp)); }

    void merge(forward_list &x) { merge(x, less<value_type>()); }

    template<class _Compare>
    void merge(forward_list &x, _Compare __comp);

    void sort() { sort(less<value_type>()); }

    template<class _Compare>
    void sort(_Compare __comp);

    void reverse() noexcept;

private:

    void __move_assign(forward_list &x, true_type) noexcept(is_nothrow_move_assignable<allocator_type>::value);

    void __move_assign(forward_list &x, false_type);

    template<class _Compare>
    static
    node_pointer
    __merge(node_pointer __f1, node_pointer __f2, _Compare &__comp);

    template<class _Compare>
    static
    node_pointer
    __sort(node_pointer __f, difference_type __sz, _Compare &__comp);
};

template<class T, class Allocator>
inline
forward_list<T, Allocator>::forward_list(const allocator_type &a) : base(a) {}

template<class T, class Allocator>
forward_list<T, Allocator>::forward_list(size_type n) {
    if (n > 0) {
        node_allocator &a = base::alloc();
        using Dp = allocator_destructor<node_allocator>;
        unique_ptr<node, Dp> h(nullptr, Dp(a, 1));
        for (node_pointer p = base::before_begin(); n > 0; --n,
                p = p->next_) {
            h.reset(node_traits::allocate(a, 1));
            node_traits::construct(a, std::addressof(h->value_));
            h->next_ = nullptr;
            p->next_ = h.release();
        }
    }
}

template<class T, class Allocator>
forward_list<T, Allocator>::forward_list(size_type n, const allocator_type &a) : base(a) {
    if (n > 0) {
        node_allocator &__a = base::alloc();
        using Dp = allocator_destructor<node_allocator>;
        unique_ptr<node, Dp> h(nullptr, Dp(a, 1));
        for (node_pointer p = base::before_begin(); n > 0; --n,
                p = p->next_) {
            h.reset(node_traits::allocate(a, 1));
            node_traits::construct(a, std::addressof(h->value_));
            h->next_ = nullptr;
            p->next_ = h.release();
        }
    }
}

template<class T, class Allocator>
forward_list<T, Allocator>::forward_list(size_type n, const value_type &v) {
    insert_after(cbefore_begin(), n, v);
}

template<class T, class Allocator>
forward_list<T, Allocator>::forward_list(size_type n, const value_type &v,
                                         const allocator_type &a)
        : base(a) {
    insert_after(cbefore_begin(), n, v);
}

template<class T, class Allocator>
template<class InputIterator>
forward_list<T, Allocator>::forward_list(InputIterator f, InputIterator l,
                                         std::iterator_traits<InputIterator>::value_type *) {
    insert_after(cbefore_begin(), f, l);
}

template<class T, class Allocator>
template<class InputIterator>
forward_list<T, Allocator>::forward_list(InputIterator f, InputIterator l,
                                         const allocator_type &__a, std::iterator_traits<InputIterator>::value_type *)
        : base(__a) {
    insert_after(cbefore_begin(), f, l);
}

template<class T, class Allocator>
forward_list<T, Allocator>::forward_list(const forward_list &x) : base(
        allocator_type(node_traits::select_on_container_copy_construction(x.__alloc()))) {
    insert_after(cbefore_begin(), x.begin(), x.end());
}

template<class T, class Allocator>
forward_list<T, Allocator>::forward_list(const forward_list &x, const allocator_type &a) : base(a) {
    insert_after(cbefore_begin(), x.begin(), x.end());
}

template<class T, class Allocator>
forward_list<T, Allocator>::forward_list(forward_list &&x, const allocator_type &a) : base(std::move(x), a) {
    if (base::alloc() != x.alloc()) {
        typedef move_iterator<iterator> Ip;
        insert_after(cbefore_begin(), Ip(x.begin()), Ip(x.end()));
    }
}

template<class T, class Allocator>
forward_list<T, Allocator>::forward_list(initializer_list<value_type> __il) {
    insert_after(cbefore_begin(), __il.begin(), __il.end());
}

template<class T, class Allocator>
forward_list<T, Allocator>::forward_list(initializer_list<value_type> __il, const allocator_type &__a) : base(__a) {
    insert_after(cbefore_begin(), __il.begin(), __il.end());
}

template<class T, class Allocator>
forward_list<T, Allocator> &
forward_list<T, Allocator>::operator=(const forward_list &x) {
    if (this != &x) {
        base::__copy_assign_alloc(x);
        assign(x.begin(), x.end());
    }
    return *this;
}

template<class T, class Allocator>
void
forward_list<T, Allocator>::__move_assign(forward_list &x, true_type)

noexcept(is_nothrow_move_assignable<allocator_type>::value) {
    clear();
    base::__move_assign_alloc(x);
    base::before_begin()->next_ = x.before_begin()->next_;
    x.before_begin()->next_ = nullptr;
}

template<class T, class Allocator>
void
forward_list<T, Allocator>::__move_assign(forward_list &x, false_type) {
    if (base::alloc() == x.alloc())
        __move_assign(x, true_type());
    else {
        using Ip = move_iterator<iterator>;
        assign(Ip(x.begin()), Ip(x.end()));
    }
}

template<class T, class Allocator>
inline
forward_list<T, Allocator> &forward_list<T, Allocator>::operator=(forward_list &&x) noexcept(
node_traits::propagate_on_container_move_assignment::value && is_nothrow_move_assignable<allocator_type>::value) {
    __move_assign(x, integral_constant<bool, node_traits::propagate_on_container_move_assignment::value>());
    return *this;
}

template<class T, class Allocator>
inline
forward_list<T, Allocator> &
forward_list<T, Allocator>::operator=(initializer_list<value_type> il) {
    assign(il.begin(), il.end());
    return *this;
}

template<class T, class Allocator>
template<class InputIterator>
//typename enable_if
//        <
//                is_input_iterator<InputIterator>::value,
//                void
//        >::type
std::iterator_traits<InputIterator>::value_type
forward_list<T, Allocator>::assign(InputIterator f, InputIterator l) {
    iterator i = before_begin();
    iterator j = std::next(i);
    iterator e = end();
    for (; j != e && f != l; ++i, (void) ++j, ++f)
        *j = *f;
    if (j == e)
        insert_after(i, f, l);
    else
        erase_after(i, e);
}

template<class T, class Allocator>
void
forward_list<T, Allocator>::assign(size_type n, const value_type &v) {
    iterator i = before_begin();
    iterator j = std::next(i);
    iterator e = end();
    for (; j != e && n > 0; --n, ++i, ++j)
        *j = v;
    if (j == e)
        insert_after(i, n, v);
    else
        erase_after(i, e);
}

template<class T, class Allocator>
inline
void
forward_list<T, Allocator>::assign(initializer_list<value_type> il) {
    assign(il.begin(), il.end());
}

template<class T, class Allocator>
template<class... Args>
void
forward_list<T, Allocator>::emplace_front(Args &&... args) {
    node_allocator &a = base::alloc();
    using Dp = allocator_destructor<node_allocator>;
    unique_ptr<node, Dp> h(node_traits::allocate(a, 1), Dp(a, 1));
    node_traits::construct(a, std::addressof(h->value_), std::forward<Args>(args)...);
    h->next_ = base::before_begin()->next_;
    base::before_begin()->next_ = h.release();
}

template<class T, class Allocator>
void
forward_list<T, Allocator>::push_front(value_type &&v) {
    node_allocator &a = base::alloc();
    using Dp = allocator_destructor<node_allocator>;
    unique_ptr<node, Dp> h(node_traits::allocate(a, 1), Dp(a, 1));
    node_traits::construct(a, std::addressof(h->value_), std::move(v));
    h->next_ = base::before_begin()->next_;
    base::before_begin()->next_ = h.release();
}

template<class T, class Allocator>
void
forward_list<T, Allocator>::push_front(const value_type &__v) {
    node_allocator &a = base::alloc();
    using Dp = allocator_destructor<node_allocator>;
    unique_ptr<node, Dp> h(node_traits::allocate(a, 1), Dp(a, 1));
    node_traits::construct(a, std::addressof(h->value_), __v);
    h->next_ = base::before_begin()->next_;
    base::before_begin()->next_ = h.release();
}

template<class T, class Allocator>
void
forward_list<T, Allocator>::pop_front() {
    node_allocator &a = base::alloc();
    node_pointer p = base::before_begin()->next_;
    base::before_begin()->next_ = p->next_;
    node_traits::destroy(a, std::addressof(p->value_));
    node_traits::deallocate(a, p, 1);
}

template<class T, class Allocator>
template<class... Args>
typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::emplace_after(const_iterator p, Args &&... __args) {
    node_pointer const __r = p.ptr_;
    node_allocator &__a = base::alloc();
    typedef allocator_destructor<node_allocator> _Dp;
    unique_ptr<node, _Dp> __h(node_traits::allocate(__a, 1), _Dp(__a, 1));
    node_traits::construct(__a, std::addressof(__h->value_),
                           std::forward<Args>(__args)...);
    __h->next_ = __r->next_;
    __r->next_ = __h.release();
    return iterator(__r->next_);
}

template<class T, class Allocator>
typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::insert_after(const_iterator __p, value_type &&__v) {
    node_pointer const __r = __p.ptr_;
    node_allocator &__a = base::alloc();
    typedef allocator_destructor<node_allocator> _Dp;
    unique_ptr<node, _Dp> __h(node_traits::allocate(__a, 1), _Dp(__a, 1));
    node_traits::construct(__a, std::addressof(__h->value_), std::move(__v));
    __h->next_ = __r->next_;
    __r->next_ = __h.release();
    return iterator(__r->next_);
}

template<class T, class Allocator>
typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::insert_after(const_iterator __p, const value_type &__v) {
    node_pointer const __r = __p.ptr_;
    node_allocator &__a = base::alloc();
    typedef allocator_destructor<node_allocator> _Dp;
    unique_ptr<node, _Dp> __h(node_traits::allocate(__a, 1), _Dp(__a, 1));
    node_traits::construct(__a, std::addressof(__h->value_), __v);
    __h->next_ = __r->next_;
    __r->next_ = __h.release();
    return iterator(__r->next_);
}

template<class T, class Allocator>
typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::insert_after(const_iterator __p, size_type __n, const value_type &__v) {
    node_pointer __r = __p.ptr_;
    if (__n > 0) {
        node_allocator &__a = base::alloc();
        typedef allocator_destructor<node_allocator> _Dp;
        unique_ptr<node, _Dp> __h(node_traits::allocate(__a, 1), _Dp(__a, 1));
        node_traits::construct(__a, std::addressof(__h->value_), __v);
        node_pointer __first = __h.release();
        node_pointer __last = __first;
        try {
            for (--__n; __n != 0; --__n, __last = __last->next_) {
                __h.reset(node_traits::allocate(__a, 1));
                node_traits::construct(__a, std::addressof(__h->value_), __v);
                __last->next_ = __h.release();
            }
        }
        catch (...) {
            while (__first != nullptr) {
                node_pointer __next = __first->next_;
                node_traits::destroy(__a, std::addressof(__first->value_));
                node_traits::deallocate(__a, __first, 1);
                __first = __next;
            }
            throw;
        }
        __last->next_ = __r->next_;
        __r->next_ = __first;
        __r = __last;
    }
    return iterator(__r);
}

template<class T, class Allocator>
template<class InputIterator>
typename enable_if<is_input_iterator<InputIterator>::value, typename forward_list<T, Allocator>::iterator>::type
forward_list<T, Allocator>::insert_after(const_iterator __p, InputIterator __f, InputIterator __l) {
    node_pointer __r = __p.ptr_;
    if (__f != __l) {
        node_allocator &__a = base::alloc();
        typedef allocator_destructor<node_allocator> _Dp;
        unique_ptr<node, _Dp> __h(node_traits::allocate(__a, 1), _Dp(__a, 1));
        node_traits::construct(__a, std::addressof(__h->value_), *__f);
        node_pointer __first = __h.release();
        node_pointer __last = __first;
        try {
            for (++__f; __f != __l; ++__f, ((void) (__last = __last->next_))) {
                __h.reset(node_traits::allocate(__a, 1));
                node_traits::construct(__a, std::addressof(__h->value_), *__f);
                __last->next_ = __h.release();
            }
        }
        catch (...) {
            while (__first != nullptr) {
                node_pointer __next = __first->next_;
                node_traits::destroy(__a, std::addressof(__first->value_));
                node_traits::deallocate(__a, __first, 1);
                __first = __next;
            }
            throw;
        }
        __last->next_ = __r->next_;
        __r->next_ = __first;
        __r = __last;
    }
    return iterator(__r);
}

template<class T, class Allocator>
typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::erase_after(const_iterator __f) {
    node_pointer __p = __f.ptr_;
    node_pointer __n = __p->next_;
    __p->next_ = __n->next_;
    node_allocator &__a = base::alloc();
    node_traits::destroy(__a, std::addressof(__n->value_));
    node_traits::deallocate(__a, __n, 1);
    return iterator(__p->next_);
}

template<class T, class Allocator>
typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::erase_after(const_iterator __f, const_iterator __l) {
    node_pointer __e = __l.ptr_;
    if (__f != __l) {
        node_pointer __p = __f.ptr_;
        node_pointer __n = __p->next_;
        if (__n != __e) {
            __p->next_ = __e;
            node_allocator &__a = base::alloc();
            do {
                __p = __n->next_;
                node_traits::destroy(__a, std::addressof(__n->value_));
                node_traits::deallocate(__a, __n, 1);
                __n = __p;
            } while (__n != __e);
        }
    }
    return iterator(__e);
}

template<class T, class Allocator>
void
forward_list<T, Allocator>::resize(size_type __n) {
    size_type __sz = 0;
    iterator __p = before_begin();
    iterator __i = begin();
    iterator __e = end();
    for (; __i != __e && __sz < __n; ++__p, ++__i, ++__sz);
    if (__i != __e)
        erase_after(__p, __e);
    else {
        __n -= __sz;
        if (__n > 0) {
            node_allocator &__a = base::alloc();
            typedef allocator_destructor<node_allocator> _Dp;
            unique_ptr<node, _Dp> __h(nullptr, _Dp(__a, 1));
            for (node_pointer __ptr = __p.ptr_; __n > 0; --__n,
                    __ptr = __ptr->next_) {
                __h.reset(node_traits::allocate(__a, 1));
                node_traits::construct(__a, std::addressof(__h->value_));
                __h->next_ = nullptr;
                __ptr->next_ = __h.release();
            }
        }
    }
}

template<class T, class Allocator>
void
forward_list<T, Allocator>::resize(size_type __n, const value_type &__v) {
    size_type __sz = 0;
    iterator __p = before_begin();
    iterator __i = begin();
    iterator __e = end();
    for (; __i != __e && __sz < __n; ++__p, ++__i, ++__sz);
    if (__i != __e)
        erase_after(__p, __e);
    else {
        __n -= __sz;
        if (__n > 0) {
            node_allocator &__a = base::alloc();
            typedef allocator_destructor<node_allocator> _Dp;
            unique_ptr<node, _Dp> __h(nullptr, _Dp(__a, 1));
            for (node_pointer __ptr = __p.ptr_; __n > 0; --__n,
                    __ptr = __ptr->next_) {
                __h.reset(node_traits::allocate(__a, 1));
                node_traits::construct(__a, std::addressof(__h->value_), __v);
                __h->next_ = nullptr;
                __ptr->next_ = __h.release();
            }
        }
    }
}

template<class T, class Allocator>
void
forward_list<T, Allocator>::splice_after(const_iterator __p,
                                         forward_list &x) {
    if (!x.empty()) {
        if (__p.ptr_->next_ != nullptr) {
            const_iterator __lm1 = x.before_begin();
            while (__lm1.ptr_->next_ != nullptr)
                ++__lm1;
            __lm1.ptr_->next_ = __p.ptr_->next_;
        }
        __p.ptr_->next_ = x.before_begin()->next_;
        x.before_begin()->next_ = nullptr;
    }
}

template<class T, class Allocator>
void
forward_list<T, Allocator>::splice_after(const_iterator __p,
                                         forward_list &x,
                                         const_iterator __i) {
    const_iterator __lm1 = std::next(__i);
    if (__p != __i && __p != __lm1) {
        __i.ptr_->next_ = __lm1.ptr_->next_;
        __lm1.ptr_->next_ = __p.ptr_->next_;
        __p.ptr_->next_ = __lm1.ptr_;
    }
}

template<class T, class Allocator>
void
forward_list<T, Allocator>::splice_after(const_iterator __p,
                                         forward_list &x,
                                         const_iterator __f, const_iterator __l) {
    if (__f != __l && __p != __f) {
        const_iterator __lm1 = __f;
        while (__lm1.ptr_->next_ != __l.ptr_)
            ++__lm1;
        if (__f != __lm1) {
            __lm1.ptr_->next_ = __p.ptr_->next_;
            __p.ptr_->next_ = __f.ptr_->next_;
            __f.ptr_->next_ = __l.ptr_;
        }
    }
}

template<class T, class Allocator>
inline
void
forward_list<T, Allocator>::splice_after(const_iterator __p, forward_list &&x) {
    splice_after(__p, x);
}

template<class T, class Allocator>
inline void forward_list<T, Allocator>::splice_after(const_iterator __p, forward_list &&x, const_iterator __i) {
    splice_after(__p, x, __i);
}

template<class T, class Allocator>
inline void forward_list<T, Allocator>::splice_after(const_iterator __p,
                                                     forward_list &&x,
                                                     const_iterator __f, const_iterator __l) {
    splice_after(__p, x, __f, __l);
}

template<class T, class Allocator>
void
forward_list<T, Allocator>::remove(const value_type &__v) {
    forward_list<T, Allocator> __deleted_nodes; // collect the nodes we're removing
    iterator __e = end();
    for (iterator __i = before_begin(); __i.ptr_->next_ != nullptr;) {
        if (__i.ptr_->next_->value_ == __v) {
            iterator __j = std::next(__i, 2);
            for (; __j != __e && *__j == __v; ++__j);
            __deleted_nodes.splice_after(__deleted_nodes.before_begin(), *this, __i, __j);
            if (__j == __e)
                break;
            __i = __j;
        } else
            ++__i;
    }
}

template<class T, class Allocator>
template<class _Predicate>
void
forward_list<T, Allocator>::remove_if(_Predicate __pred) {
    iterator __e = end();
    for (iterator __i = before_begin(); __i.ptr_->next_ != nullptr;) {
        if (__pred(__i.ptr_->next_->value_)) {
            iterator __j = std::next(__i, 2);
            for (; __j != __e && __pred(*__j); ++__j);
            erase_after(__i, __j);
            if (__j == __e)
                break;
            __i = __j;
        } else
            ++__i;
    }
}

template<class T, class Allocator>
template<class _BinaryPredicate>
void
forward_list<T, Allocator>::unique(_BinaryPredicate __binary_pred) {
    for (iterator __i = begin(), __e = end(); __i != __e;) {
        iterator __j = std::next(__i);
        for (; __j != __e && __binary_pred(*__i, *__j); ++__j);
        if (__i.ptr_->next_ != __j.ptr_)
            erase_after(__i, __j);
        __i = __j;
    }
}

template<class T, class Allocator>
template<class _Compare>
void
forward_list<T, Allocator>::merge(forward_list &x, _Compare __comp) {
    if (this != &x) {
        base::before_begin()->next_ = __merge(base::before_begin()->next_,
                                              x.before_begin()->next_,
                                              __comp);
        x.before_begin()->next_ = nullptr;
    }
}

template<class T, class Allocator>
template<class _Compare>
typename forward_list<T, Allocator>::node_pointer
forward_list<T, Allocator>::__merge(node_pointer __f1, node_pointer __f2,
                                    _Compare &__comp) {
    if (__f1 == nullptr)
        return __f2;
    if (__f2 == nullptr)
        return __f1;
    node_pointer __r;
    if (__comp(__f2->value_, __f1->value_)) {
        node_pointer __t = __f2;
        while (__t->next_ != nullptr &&
               __comp(__t->next_->value_, __f1->value_))
            __t = __t->next_;
        __r = __f2;
        __f2 = __t->next_;
        __t->next_ = __f1;
    } else
        __r = __f1;
    node_pointer __p = __f1;
    __f1 = __f1->next_;
    while (__f1 != nullptr && __f2 != nullptr) {
        if (__comp(__f2->value_, __f1->value_)) {
            node_pointer __t = __f2;
            while (__t->next_ != nullptr &&
                   __comp(__t->next_->value_, __f1->value_))
                __t = __t->next_;
            __p->next_ = __f2;
            __f2 = __t->next_;
            __t->next_ = __f1;
        }
        __p = __f1;
        __f1 = __f1->next_;
    }
    if (__f2 != nullptr)
        __p->next_ = __f2;
    return __r;
}

template<class T, class Allocator>
template<class _Compare>
inline
void
forward_list<T, Allocator>::sort(_Compare __comp) {
    base::before_begin()->next_ = __sort(base::before_begin()->next_,
                                         std::distance(begin(), end()), __comp);
}

template<class T, class Allocator>
template<class _Compare>
typename forward_list<T, Allocator>::node_pointer
forward_list<T, Allocator>::__sort(node_pointer __f1, difference_type __sz,
                                   _Compare &__comp) {
    switch (__sz) {
        case 0:
        case 1:
            return __f1;
        case 2:
            if (__comp(__f1->next_->value_, __f1->value_)) {
                node_pointer __t = __f1->next_;
                __t->next_ = __f1;
                __f1->next_ = nullptr;
                __f1 = __t;
            }
            return __f1;
    }
    difference_type __sz1 = __sz / 2;
    difference_type __sz2 = __sz - __sz1;
    node_pointer __t = std::next(iterator(__f1), __sz1 - 1).ptr_;
    node_pointer __f2 = __t->next_;
    __t->next_ = nullptr;
    return __merge(__sort(__f1, __sz1, __comp),
                   __sort(__f2, __sz2, __comp), __comp);
}

template<class T, class Allocator>
void
forward_list<T, Allocator>::reverse() noexcept {
    node_pointer __p = base::before_begin()->next_;
    if (__p != nullptr) {
        node_pointer __f = __p->next_;
        __p->next_ = nullptr;
        while (__f != nullptr) {
            node_pointer __t = __f->next_;
            __f->next_ = __p;
            __p = __f;
            __f = __t;
        }
        base::before_begin()->next_ = __p;
    }
}

template<class T, class Allocator>
bool operator==(const forward_list<T, Allocator> &x,
                const forward_list<T, Allocator> &y) {
    typedef forward_list<T, Allocator> _Cp;
    typedef typename _Cp::const_iterator _Ip;
    _Ip __ix = x.begin();
    _Ip __ex = x.end();
    _Ip __iy = y.begin();
    _Ip __ey = y.end();
    for (; __ix != __ex && __iy != __ey; ++__ix, ++__iy)
        if (!(*__ix == *__iy))
            return false;
    return (__ix == __ex) == (__iy == __ey);
}

template<class T, class Allocator>
inline
bool operator!=(const forward_list<T, Allocator> &x,
                const forward_list<T, Allocator> &y) {
    return !(x == y);
}

template<class T, class Allocator>
inline
bool operator<(const forward_list<T, Allocator> &x,
               const forward_list<T, Allocator> &y) {
    return std::lexicographical_compare(x.begin(), x.end(),
                                        y.begin(), y.end());
}

template<class T, class Allocator>
inline
bool operator>(const forward_list<T, Allocator> &x,
               const forward_list<T, Allocator> &y) {
    return y < x;
}

template<class T, class Allocator>
inline
bool operator>=(const forward_list<T, Allocator> &x,
                const forward_list<T, Allocator> &y) {
    return !(x < y);
}

template<class T, class Allocator>
inline
bool operator<=(const forward_list<T, Allocator> &x,
                const forward_list<T, Allocator> &y) {
    return !(y < x);
}

template<class T, class Allocator>
inline
void swap(forward_list<T, Allocator> &x, forward_list<T, Allocator> &y) noexcept (noexcept(x.swap(y))) {
    x.swap(y);
}

#endif //CUSTOM_ALGORITHMS_FORWARD_LIST_H
