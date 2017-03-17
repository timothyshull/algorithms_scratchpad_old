#ifndef ALGORITHMS_FORWARD_LIST_H
#define ALGORITHMS_FORWARD_LIST_H

#include "comp_pair.h"
#include <initializer_list>
#include <memory>
#include <limits>
#include <iterator>
#include <algorithm>
#include <functional>

using std::initializer_list;
using std::pointer_traits;
using std::allocator_traits;
using std::allocator;
using std::forward_iterator_tag;
using std::remove_const;
using std::is_nothrow_default_constructible;
using std::is_nothrow_move_constructible;
using std::integral_constant;
using std::is_nothrow_assignable;
using std::is_nothrow_move_assignable;
using is_nothrow_swappable = std::__is_nothrow_swappable_imp;
using std::numeric_limits;
using is_input_iterator = std::__is_input_iterator;
using std::enable_if;
using allocator_destructor = std::__allocator_destructor;
using std::unique_ptr;

namespace custom_list {

    template<class T, class VoidPtr>
    struct forward_list_node;

    template<class NodePtr>
    struct begin_node {
        using pointer = NodePtr;
        pointer next;

        inline begin_node() : next{nullptr} { }
    };

    template<class T, class VoidPtr>
    struct begin_node_of {
        using type = begin_node<typename pointer_traits<VoidPtr>::template rebind<forward_list_node<T, VoidPtr>>>;
    };

    template<class T, class VoidPtr>
    struct forward_list_node : public begin_node_of<T, VoidPtr>::type {
        using value_type = T;
        value_type value;
    };

    template<class T, class Allocator = allocator<T>>
    class forward_list;

    template<class NodeConstPtr>
    class forward_list_const_iterator;


    // class _ALGO_VIS forward_list_iterator {
    template<class NodePtr>
    class forward_list_iterator {
        using node_pointer = NodePtr;
        node_pointer ptr;

        inline explicit forward_list_iterator(node_pointer p) noexcept : ptr{p} { }

        template<class, class> friend
        class forward_list; // _ALGO_VIS
        template<class> friend
        class forward_list_const_iterator; // _ALGO_VIS

    public:
        typedef forward_iterator_tag iterator_category;
        typedef typename pointer_traits<node_pointer>::element_type::value_type value_type;
        typedef value_type& reference;
        typedef typename pointer_traits<node_pointer>::difference_type difference_type;
        typedef typename pointer_traits<node_pointer>::template
        rebind<value_type> pointer;

        inline forward_list_iterator() noexcept : ptr{nullptr} { }

        reference operator*() const { return ptr->__value_; } // _ALGO_VIS
        inline pointer operator->() const { return pointer_traits<pointer>::pointer_to(ptr->value); }

        inline forward_list_iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }

        inline forward_list_iterator operator++(int) {
            forward_list_iterator it(*this);
            ++(*this);
            return it;
        }

        friend inline bool operator==(const forward_list_iterator& x, const forward_list_iterator& y) {
            return x.ptr == y.ptr;
        }

        friend inline bool operator!=(const forward_list_iterator& x, const forward_list_iterator& y) {
            return x != y;
        } // !(x == y)
    };

    // _ALGO_VIS
    template<class NodeConstPtr>
    class forward_list_const_iterator {
        using node_const_pointer = NodeConstPtr;
        node_const_pointer ptr;

        inline explicit forward_list_const_iterator(node_const_pointer p) noexcept : ptr{p} { }

        using node = remove_const<typename pointer_traits<node_const_pointer>::element_type>::type;
        using node_pointer = pointer_traits<node_const_pointer>::template rebind<node>

        template<class, class> friend
        class forward_list;

    public:
        using iterator_category = forward_iterator_tag;
        using value_type = node::value_type;
        using reference = value_type&;
        using difference_type = pointer_traits<node_const_pointer>::difference_type;
        using pointer = typename pointer_traits<node_const_pointer>::template rebind<const value_type>;

        inline forward_list_const_iterator() noexcept : ptr{nullptr} { }

        inline forward_list_const_iterator(forward_list_iterator<node_pointer> p) noexcept : ptr{p.ptr} { }

        inline reference operator*() const { return ptr->value; }

        inline pointer operator->() const { return pointer_traits<pointer>::pointer_to(ptr->value); }

        inline forward_list_const_iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }

        inline forward_list_const_iterator operator++(int) {
            forward_list_const_iterator it(*this);
            ++(*this);
            return it;
        }

        friend inline bool operator==(const forward_list_const_iterator& x,
                                      const forward_list_const_iterator& y) { return x.ptr == y.ptr; }

        friend inline bool operator!=(const forward_list_const_iterator& x,
                                      const forward_list_const_iterator& y) { return !(x == y); }
    };


    template<class T, class Allocator>
    class forward_list_base {
    protected:
        using value_type = T;
        using allocator_type = Allocator;

        using void_pointer = typename allocator_traits<allocator_type>::void_pointer;
        using node = forward_list_node<value_type, void_pointer>;
        using begin_node = begin_node_of<value_type, void_pointer>::type;
        using node_allocator = allocator_traits<allocator_type>::template rebind_alloc<node>;
        using node_traits = allocator_traits<node_allocator>;
        using node_pointer = node_traits::pointer;
        using node_const_pointer = node_traits::pointer;

        using begin_node_allocator = typename allocator_traits<allocator_type>::template rebind_alloc<begin_node>;
        using begin_node_pointer = typename allocator_traits<begin_node_allocator>::pointer;

        compressed_pair<begin_node, node_allocator> before_begin_;

        inline node_pointer before_begin() noexcept {
            return static_cast<node_pointer>(pointer_traits<begin_node_pointer>::pointer_to(before_begin_.first()));
        }

        inline node_const_pointer before_begin() const noexcept {
            return static_cast<node_const_pointer>(pointer_traits<begin_node_pointer>::pointer_to(
                    const_cast<begin_node&>(before_begin_.first())));
        }

        inline node_allocator& alloc() noexcept { return before_begin_.second(); }

        inline const node_allocator& alloc() const noexcept { return before_begin_.second(); }

        using iterator = forward_list_iterator<node_pointer>;
        using const_iterator = forward_list_const_iterator<node_pointer>;

        inline forward_list_base() noexcept(is_nothrow_default_constructible<node_allocator>::value) : before_begin_(
                begin_node()) { }

        inline forward_list_base(const allocator_type& a) : before_begin_(begin_node(), node_allocator(a)) { }

    public:
        forward_list_base(forward_list_base&& x) noexcept(is_nothrow_move_constructible<node_allocator>::value);

        forward_list_base(forward_list_base&& x, const allocator_type& a);

    private:
        forward_list_base(const forward_list_base&);

        forward_list_base& operator=(const forward_list_base&);

    public:
        ~forward_list_base();

    protected:
        inline void copy_assign_alloc(const forward_list_base& x) {
            copy_assign_alloc(x, integral_constant<bool, node_traits::propagate_on_container_copy_assignment::value>());
        }

        inline void move_assign_alloc(forward_list_base& x) noexcept(
        !node_traits::propagate_on_container_move_assignment::value ||
        is_nothrow_move_assignable<node_allocator>::value) {
            move_assign_alloc(x, integral_constant<bool, node_traits::propagate_on_container_move_assignment::value>());
        }

    public:
        void swap(forward_list_base& x) noexcept(!node_traits::propagate_on_container_swap::value ||
                                                 is_nothrow_swappable<node_allocator>::value);

    protected:
        void clear() noexcept;

    private:
        using false_type = integral_constant<bool, false>;
        using true_type = integral_constant<bool, true>;

        inline void copy_assign_alloc(const forward_list_base&, false_type) { }

        inline void copy_assign_alloc(const forward_list_base& x, true_type) {
            if (alloc() != x.alloc())
                clear();
            alloc() = x.alloc();
        }

        inline void move_assign_alloc(forward_list_base& __x, false_type) noexcept { }

        inline void move_assign_alloc(forward_list_base& x,
                                      true_type) noexcept(is_nothrow_move_assignable<node_allocator>::value) {
            alloc() = std::move(x.alloc());
        }

        inline static void swap_alloc(node_allocator& x, node_allocator& y) noexcept(
        !node_traits::propagate_on_container_swap::value || is_nothrow_swappable<node_allocator>::value) {
            swap_alloc(x, y, integral_constant<bool, node_traits::propagate_on_container_swap::value>());
        }

        inline static void swap_alloc(node_allocator& x, node_allocator& y, false_type) noexcept { }

        inline static void swap_alloc(node_allocator& x, node_allocator& y,
                                      true_type) noexcept(is_nothrow_swappable<node_allocator>::value) {
            std::swap(x, y);
        }
    };

    template<class T, class Alloc>
    inline forward_list_base<T, Alloc>::forward_list_base(
            forward_list_base&& x) noexcept(is_nothrow_move_constructible<node_allocator>::value)
            : before_begin_(std::move(x.before_begin_)) {
        x.before_begin()->next = nullptr;
    }

    template<class T, class Alloc>
    inline forward_list_base<T, Alloc>::forward_list_base(forward_list_base&& x, const allocator_type& a)
            : before_begin_(begin_node(), node_allocator(a)) {
        if (alloc() == x.alloc()) {
            before_begin()->next = x.before_begin()->next;
            x.before_begin()->next = nullptr;
        }
    }

    template<class T, class Alloc>
    forward_list_base<T, Alloc>::~forward_list_base() {
        clear();
    }

    template<class T, class Allocator>
    inline void forward_list_base<T, Allocator>::swap(forward_list_base& x)
    noexcept(!node_traits::propagate_on_container_swap::value || std::__is_nothrow_swappable<node_allocator>::value) {
        swap_alloc(alloc(), x.alloc());
        std::swap(before_begin()->next, x.before_begin()->next);
    }

    template<class T, class Alloc>
    void forward_list_base<T, Alloc>::clear() noexcept {
        node_allocator& a = alloc();
        for (node_pointer p = before_begin()->next; p != nullptr;) {
            node_pointer __next = p->next;
            node_traits::destroy(a, std::addressof(p->value));
            node_traits::deallocate(a, p, 1);
            p = __next;
        }
        before_begin()->__next_ = nullptr;
    }


    template<class T, class Allocator = allocator<T>>
    class forward_list : forward_list_base<T, Allocator> {
        using base = forward_list_base<T, Allocator>;
        using node_allocator = base::node_allocator;
        using node = base::node;
        using node_traits = base::node_traits;
        using node_pointer = base::node_pointer;

    public:
        using value_type = T;
        using allocator_type = Allocator;

        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = allocator_traits<allocator_type>::pointer;
        using const_pointer = allocator_traits<allocator_type>::const_pointer;
        using size_type = allocator_traits<allocator_type>::size_type;
        using difference_type = allocator_traits<allocator_type>::difference_type;

//        using iterator = forward_list_iterator;
//        using const_iterator = forward_list_const_iterator;

        using iterator = base::iterator;
        using const_iterator = base::const_iterator;


        inline forward_list() noexcept(is_nothrow_default_constructible<node_allocator>::value);

        explicit forward_list(const allocator_type& a);

        explicit forward_list(size_type n);

        explicit forward_list(size_type n, const allocator_type& a); // C++14

        forward_list(size_type n, const value_type& v);

        forward_list(size_type n, const value_type& v, const allocator_type& a);

        template<class InputIterator>
        forward_list(InputIterator first, InputIterator last,
                     typename enable_if<is_input_iterator<InputIterator>::value>::type* = nullptr);

        template<class InputIterator>
        forward_list(InputIterator first, InputIterator last, const allocator_type& a,
                     typename enable_if<is_input_iterator<InputIterator>::value>::type* = nullptr);

        forward_list(const forward_list& x);

        forward_list(const forward_list& x, const allocator_type& a);

        inline forward_list(forward_list&& x) noexcept(is_nothrow_move_constructible<allocator_type>::value) : base(
                std::move(x)) { }

        forward_list(forward_list&& x, const allocator_type& a);

        forward_list(initializer_list<value_type> il);

        forward_list(initializer_list<value_type> il, const allocator_type& a);


        // ~forward_list() = default;



        forward_list& operator=(const forward_list& x);

        forward_list& operator=(forward_list&& x)
                noexcept(
                node_traits::propagate_on_container_move_assignment::value &&
                is_nothrow_move_assignable<allocator_type>::value);

        forward_list& operator=(initializer_list<value_type> il);

        template<class InputIterator>
        typename enable_if<is_input_iterator<InputIterator>::value, void>::type
                assign(InputIterator first, InputIterator last);

        void assign(size_type n, const value_type& v);

        void assign(initializer_list<value_type> il);


        inline allocator_type get_allocator() const noexcept { return allocator_type(base::alloc()); }

        inline iterator begin() noexcept { return iterator(base::before_begin()->__next_); }

        inline const_iterator begin() const noexcept { return const_iterator(base::before_begin()->__next_); }

        inline iterator end() noexcept { return iterator(nullptr); }

        inline const_iterator end() const noexcept { return const_iterator(nullptr); }

        inline const_iterator cbegin() const noexcept { return const_iterator(base::before_begin()->__next_); }

        inline const_iterator cend() const noexcept { return const_iterator(nullptr); }

        inline iterator before_begin() noexcept { return iterator(base::before_begin()); }

        inline const_iterator before_begin() const noexcept { return const_iterator(base::before_begin()); }

        inline const_iterator cbefore_begin() const noexcept { return const_iterator(base::before_begin()); }

        inline bool empty() const noexcept { return base::before_begin()->__next_ == nullptr; }

        inline size_type max_size() const noexcept { return numeric_limits<size_type>::max(); }

        inline reference front() { return base::before_begin()->__next_->__value_; }

        inline const_reference front() const { return base::before_begin()->__next_->__value_; }


        template<class... Args>
        void emplace_front(Args&& ... args);

        void push_front(value_type&& v);

        void push_front(const value_type& v);

        void pop_front();

        template<class... Args>
        iterator emplace_after(const_iterator p, Args&& ... args);

        iterator insert_after(const_iterator p, value_type&& v);

        iterator insert_after(const_iterator p, const value_type& v);

        iterator insert_after(const_iterator p, size_type n, const value_type& v);

        template<class InputIterator>
        inline typename enable_if<is_input_iterator<InputIterator>::value, iterator>::type
                insert_after(const_iterator p, InputIterator first, InputIterator last);

        iterator insert_after(const_iterator p, initializer_list<value_type> il) {
            return insert_after(p, il.begin(), il.end());
        }

        iterator erase_after(const_iterator p);

        iterator erase_after(const_iterator first, const_iterator last);

        inline void swap(forward_list& x)
        noexcept(!node_traits::propagate_on_container_swap::value ||
                 is_nothrow_swappable<node_allocator>::value) { base::swap(x); }

        void resize(size_type n);

        void resize(size_type n, const value_type& v);

        inline void clear() noexcept { base::clear(); }

        inline
        void splice_after(const_iterator p, forward_list&& x);

        inline
        void splice_after(const_iterator p, forward_list&& x, const_iterator it);

        inline
        void splice_after(const_iterator p, forward_list&& x,
                          const_iterator first, const_iterator last);

        void splice_after(const_iterator p, forward_list& x);

        void splice_after(const_iterator p, forward_list& x, const_iterator it);

        void splice_after(const_iterator p, forward_list& x,
                          const_iterator first, const_iterator last);

        void remove(const value_type& v);

        template<class Predicate>
        void remove_if(Predicate pred);

        inline
        void unique() { unique(std::equal_to<value_type>()); }

        template<class BinaryPredicate>
        void unique(BinaryPredicate binary_pred);

        inline
        void merge(forward_list&& x) { merge(x, std::less<value_type>()); }

        template<class Compare>
        inline
        void merge(forward_list&& x, Compare comp) { merge(x, std::move(comp)); }

        inline
        void merge(forward_list& x) { merge(x, std::less<value_type>()); }

        template<class Compare>
        void merge(forward_list& x, Compare comp);

        inline
        void sort() { sort(std::less<value_type>()); }

        template<class Compare>
        void sort(Compare comp);

        void reverse() noexcept;

    private:

        void move_assign(forward_list& x, true_type) noexcept(is_nothrow_move_assignable<allocator_type>::value);

        void move_assign(forward_list& x, false_type);

        template<class Compare>
        static node_pointer merge(node_pointer first1, node_pointer first2, Compare& comp);

        template<class Compare>
        static node_pointer sort(node_pointer first, difference_type sz, Compare& comp);
    };

    template<class T, class Allocator>
    inline forward_list<T, Allocator>::forward_list(const allocator_type& a) : base(a) { }

    template<class T, class Allocator>
    forward_list<T, Allocator>::forward_list(size_type n) {
        if (n > 0) {
            node_allocator& a = base::alloc();
            using Dp = allocator_destructor<node_allocator>;
            unique_ptr<node, Dp> h(nullptr, Dp(a, 1));
            for (node_pointer p = base::before_begin(); n > 0; --n,
                    p = p->next_) {
                h.reset(node_traits::allocate(a, 1));
                node_traits::construct(a, std::addressof(h->value));
                h->next = nullptr;
                p->next = h.release();
            }
        }
    }

    template<class T, class Allocator>
    forward_list<T, Allocator>::forward_list(size_type n, const allocator_type& a) : base(a) {
        if (n > 0) {
            node_allocator& allocator1 = base::alloc();
            using Dp = allocator_destructor<node_allocator>;
            unique_ptr<node, Dp> h(nullptr, Dp(allocator1, 1));
            for (node_pointer p = base::before_begin(); n > 0; --n, p = p->next) {
                h.reset(node_traits::allocate(allocator1, 1));
                node_traits::construct(allocator1, std::addressof(h->value));
                h->next = nullptr;
                p->next = h.release();
            }
        }
    }

    template<class T, class Allocator>
    forward_list<T, Allocator>::forward_list(size_type n, const value_type& v) {
        insert_after(cbefore_begin(), n, v);
    }

    template<class T, class Allocator>
    forward_list<T, Allocator>::forward_list(size_type n, const value_type& v, const allocator_type& a) : base(a) {
        insert_after(cbefore_begin(), n, v);
    }

    template<class T, class Allocator>
    template<class _InputIterator>
    forward_list<T, Allocator>::forward_list(_InputIterator first, _InputIterator last,
                                             typename enable_if<is_input_iterator<_InputIterator>::value>::type*) {
        insert_after(cbefore_begin(), first, last);
    }

    template<class T, class Allocator>
    template<class _InputIterator>
    forward_list<T, Allocator>::forward_list(_InputIterator first, _InputIterator last, const allocator_type& a,
                                             typename enable_if<is_input_iterator<_InputIterator>::value>::type*)
            : base(a) {
        insert_after(cbefore_begin(), first, last);
    }

    template<class T, class Allocator>
    forward_list<T, Allocator>::forward_list(const forward_list& x) : base(allocator_type(
            node_traits::select_on_container_copy_construction(x.alloc()))) {
        insert_after(cbefore_begin(), x.begin(), x.end());
    }

    template<class T, class Allocator>
    forward_list<T, Allocator>::forward_list(const forward_list& __x, const allocator_type& a) : base(a) {
        insert_after(cbefore_begin(), __x.begin(), __x.end());
    }

    template<class T, class Allocator>
    forward_list<T, Allocator>::forward_list(forward_list&& x, const allocator_type& a) : base(std::move(x), a) {
        if (base::alloc() != x.alloc()) {
            using Ip = std::move_iterator<iterator>;
            insert_after(cbefore_begin(), Ip(x.begin()), Ip(x.end()));
        }
    }

    template<class T, class Allocator>
    forward_list<T, Allocator>::forward_list(initializer_list<value_type> il) {
        insert_after(cbefore_begin(), il.begin(), il.end());
    }

    template<class T, class Allocator>
    forward_list<T, Allocator>::forward_list(initializer_list<value_type> il,
                                             const allocator_type& a)
            : base(a) {
        insert_after(cbefore_begin(), il.begin(), il.end());
    }

    template<class T, class Allocator>
    forward_list<T, Allocator>& forward_list<T, Allocator>::operator=(const forward_list& x) {
        if (this != &x) {
            base::copy_assign_alloc(x);
            assign(x.begin(), x.end());
        }
        return *this;
    }

    template<class T, class Allocator>
    void forward_list<T, Allocator>::move_assign(forward_list& __x, true_type)
    noexcept(is_nothrow_move_assignable<allocator_type>::value) {
        clear();
        base::move_assign_alloc(__x);
        base::before_begin()->next_ = __x.before_begin()->next_;
        __x.before_begin()->next_ = nullptr;
    }

    template<class T, class Allocator>
    void forward_list<T, Allocator>::move_assign(forward_list& __x, false_type) {
        if (base::alloc() == __x.alloc())
            move_assign(__x, true_type());
        else {
            using Ip = std::move_iterator<iterator>;
            assign(Ip(__x.begin()), Ip(__x.end()));
        }
    }

    template<class T, class Allocator>
    inline forward_list<T, Allocator>& forward_list<T, Allocator>::operator=(forward_list&& __x) noexcept(
    node_traits::propagate_on_container_move_assignment::value &&
    is_nothrow_move_assignable<allocator_type>::value) {
        move_assign(__x, integral_constant<bool,
                node_traits::propagate_on_container_move_assignment::value>());
        return *this;
    }

    template<class T, class Allocator>
    inline forward_list<T, Allocator>& forward_list<T, Allocator>::operator=(initializer_list<value_type> __il) {
        assign(__il.begin(), __il.end());
        return *this;
    }

    template<class T, class Allocator>
    template<class _InputIterator>
    typename enable_if<is_input_iterator<_InputIterator>::value, void>::type
    forward_list<T, Allocator>::assign(_InputIterator __f, _InputIterator __l) {
        iterator __i = before_begin();
        iterator __j = std::next(__i);
        iterator __e = end();
        for (; __j != __e && __f != __l; ++__i, (void) ++__j, ++__f)
            *__j = *__f;
        if (__j == __e)
            insert_after(__i, __f, __l);
        else
            erase_after(__i, __e);
    }

    template<class T, class Allocator>
    void forward_list<T, Allocator>::assign(size_type n, const value_type& __v) {
        iterator __i = before_begin();
        iterator __j = std::next(__i);
        iterator __e = end();
        for (; __j != __e && n > 0; --n, ++__i, ++__j)
            *__j = __v;
        if (__j == __e)
            insert_after(__i, n, __v);
        else
            erase_after(__i, __e);
    }

    template<class T, class Allocator>
    inline void forward_list<T, Allocator>::assign(initializer_list<value_type> __il) {
        assign(__il.begin(), __il.end());
    }

    template<class T, class Allocator>
    template<class... _Args>
    void forward_list<T, Allocator>::emplace_front(_Args&& ... args) {
        node_allocator& a = base::alloc();
        typedef allocator_destructor<node_allocator> Dp;
        unique_ptr<node, Dp> h(node_traits::allocate(a, 1), Dp(a, 1));
        node_traits::construct(a, std::addressof(h->value),
                               std::forward<_Args>(args)...);
        h->next_ = base::before_begin()->next_;
        base::before_begin()->next_ = h.release();
    }

    template<class T, class Allocator>
    void forward_list<T, Allocator>::push_front(value_type&& __v) {
        node_allocator& a = base::alloc();
        typedef allocator_destructor<node_allocator> Dp;
        unique_ptr<node, Dp> h(node_traits::allocate(a, 1), Dp(a, 1));
        node_traits::construct(a, std::addressof(h->value), std::move(__v));
        h->next_ = base::before_begin()->next_;
        base::before_begin()->next_ = h.release();
    }

    template<class T, class Allocator>
    void forward_list<T, Allocator>::push_front(const value_type& __v) {
        node_allocator& a = base::alloc();
        typedef allocator_destructor<node_allocator> Dp;
        unique_ptr<node, Dp> h(node_traits::allocate(a, 1), Dp(a, 1));
        node_traits::construct(a, std::addressof(h->value), __v);
        h->next_ = base::before_begin()->next_;
        base::before_begin()->next_ = h.release();
    }

    template<class T, class Allocator>
    void forward_list<T, Allocator>::pop_front() {
        node_allocator& a = base::alloc();
        node_pointer p = base::before_begin()->next_;
        base::before_begin()->next_ = p->next_;
        node_traits::destroy(a, std::addressof(p->value));
        node_traits::deallocate(a, p, 1);
    }

    template<class T, class Allocator>
    template<class... _Args>
    typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::emplace_after(const_iterator p, _Args&& ... args) {
        node_pointer const __r = p.ptr;
        node_allocator& a = base::alloc();
        typedef allocator_destructor<node_allocator> Dp;
        unique_ptr<node, Dp> h(node_traits::allocate(a, 1), Dp(a, 1));
        node_traits::construct(a, std::addressof(h->value),
                               std::forward<_Args>(args)...);
        h->next_ = __r->next_;
        __r->next_ = h.release();
        return iterator(__r->next_);
    }

    template<class T, class Allocator>
    typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::insert_after(const_iterator p, value_type&& __v) {
        node_pointer const __r = p.ptr;
        node_allocator& a = base::alloc();
        typedef allocator_destructor<node_allocator> Dp;
        unique_ptr<node, Dp> h(node_traits::allocate(a, 1), Dp(a, 1));
        node_traits::construct(a, std::addressof(h->value), std::move(__v));
        h->next_ = __r->next_;
        __r->next_ = h.release();
        return iterator(__r->next_);
    }

    template<class T, class Allocator>
    typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::insert_after(const_iterator p, const value_type& __v) {
        node_pointer const __r = p.ptr;
        node_allocator& a = base::alloc();
        typedef allocator_destructor<node_allocator> Dp;
        unique_ptr<node, Dp> h(node_traits::allocate(a, 1), Dp(a, 1));
        node_traits::construct(a, std::addressof(h->value), __v);
        h->next_ = __r->next_;
        __r->next_ = h.release();
        return iterator(__r->next_);
    }

    template<class T, class Allocator>
    typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::insert_after(const_iterator p, size_type n,
                                             const value_type& __v) {
        node_pointer __r = p.ptr;
        if (n > 0) {
            node_allocator& a = base::alloc();
            typedef allocator_destructor<node_allocator> Dp;
            unique_ptr<node, Dp> h(node_traits::allocate(a, 1), Dp(a, 1));
            node_traits::construct(a, std::addressof(h->value), __v);
            node_pointer __first = h.release();
            node_pointer __last = __first;
            try {
                for (--n; n != 0; --n, __last = __last->next_) {
                    h.reset(node_traits::allocate(a, 1));
                    node_traits::construct(a, std::addressof(h->value), __v);
                    __last->next_ = h.release();
                }
            }
            catch (...) {
                while (__first != nullptr) {
                    node_pointer next = __first->next_;
                    node_traits::destroy(a, std::addressof(__first->value));
                    node_traits::deallocate(a, __first, 1);
                    __first = next;
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
    typename enable_if
            <is_input_iterator<InputIterator>::value, typename forward_list<T, Allocator>::iterator>::type
    forward_list<T, Allocator>::insert_after(const_iterator p,
                                             InputIterator __f, InputIterator __l) {
        node_pointer __r = p.ptr;
        if (__f != __l) {
            node_allocator& a = base::alloc();
            typedef allocator_destructor<node_allocator> Dp;
            unique_ptr<node, Dp> h(node_traits::allocate(a, 1), Dp(a, 1));
            node_traits::construct(a, std::addressof(h->value), *__f);
            node_pointer __first = h.release();
            node_pointer __last = __first;
            try {
                for (++__f; __f != __l; ++__f, ((void) (__last = __last->next_))) {
                    h.reset(node_traits::allocate(a, 1));
                    node_traits::construct(a, std::addressof(h->value), *__f);
                    __last->next_ = h.release();
                }
            }
            catch (...) {
                while (__first != nullptr) {
                    node_pointer next = __first->next_;
                    node_traits::destroy(a, std::addressof(__first->value));
                    node_traits::deallocate(a, __first, 1);
                    __first = next;
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
        node_pointer p = __f.ptr;
        node_pointer n = p->next_;
        p->next_ = n->next_;
        node_allocator& a = base::alloc();
        node_traits::destroy(a, std::addressof(n->value));
        node_traits::deallocate(a, n, 1);
        return iterator(p->next_);
    }

    template<class T, class Allocator>
    typename forward_list<T, Allocator>::iterator
    forward_list<T, Allocator>::erase_after(const_iterator __f, const_iterator __l) {
        node_pointer __e = __l.ptr;
        if (__f != __l) {
            node_pointer p = __f.ptr;
            node_pointer n = p->next_;
            if (n != __e) {
                p->next_ = __e;
                node_allocator& a = base::alloc();
                do {
                    p = n->next_;
                    node_traits::destroy(a, std::addressof(n->value));
                    node_traits::deallocate(a, n, 1);
                    n = p;
                } while (n != __e);
            }
        }
        return iterator(__e);
    }

    template<class T, class Allocator>
    void
    forward_list<T, Allocator>::resize(size_type n) {
        size_type __sz = 0;
        iterator p = before_begin();
        iterator __i = begin();
        iterator __e = end();
        for (; __i != __e && __sz < n; ++p, ++__i, ++__sz);
        if (__i != __e)
            erase_after(p, __e);
        else {
            n -= __sz;
            if (n > 0) {
                node_allocator& a = base::alloc();
                typedef allocator_destructor<node_allocator> Dp;
                unique_ptr<node, Dp> h(nullptr, Dp(a, 1));
                for (node_pointer ptr = p.ptr; n > 0; --n,
                        ptr = ptr->next_) {
                    h.reset(node_traits::allocate(a, 1));
                    node_traits::construct(a, std::addressof(h->value));
                    h->next_ = nullptr;
                    ptr->next_ = h.release();
                }
            }
        }
    }

    template<class T, class Allocator>
    void
    forward_list<T, Allocator>::resize(size_type n, const value_type& __v) {
        size_type __sz = 0;
        iterator p = before_begin();
        iterator __i = begin();
        iterator __e = end();
        for (; __i != __e && __sz < n; ++p, ++__i, ++__sz);
        if (__i != __e)
            erase_after(p, __e);
        else {
            n -= __sz;
            if (n > 0) {
                node_allocator& a = base::alloc();
                typedef allocator_destructor<node_allocator> Dp;
                unique_ptr<node, Dp> h(nullptr, Dp(a, 1));
                for (node_pointer ptr = p.ptr; n > 0; --n,
                        ptr = ptr->next_) {
                    h.reset(node_traits::allocate(a, 1));
                    node_traits::construct(a, std::addressof(h->value), __v);
                    h->next_ = nullptr;
                    ptr->next_ = h.release();
                }
            }
        }
    }

    template<class T, class Allocator>
    void
    forward_list<T, Allocator>::splice_after(const_iterator p,
                                             forward_list& __x) {
        if (!__x.empty()) {
            if (p.ptr->next_ != nullptr) {
                const_iterator __lm1 = __x.before_begin();
                while (__lm1.ptr->next_ != nullptr)
                    ++__lm1;
                __lm1.ptr->next_ = p.ptr->next_;
            }
            p.ptr->next_ = __x.before_begin()->next_;
            __x.before_begin()->next_ = nullptr;
        }
    }

    template<class T, class Allocator>
    void
    forward_list<T, Allocator>::splice_after(const_iterator p,
                                             forward_list& __x,
                                             const_iterator __i) {
        const_iterator __lm1 = std::next(__i);
        if (p != __i && p != __lm1) {
            __i.ptr->next_ = __lm1.ptr->next_;
            __lm1.ptr->next_ = p.ptr->next_;
            p.ptr->next_ = __lm1.ptr;
        }
    }

    template<class T, class Allocator>
    void
    forward_list<T, Allocator>::splice_after(const_iterator p,
                                             forward_list& __x,
                                             const_iterator __f, const_iterator __l) {
        if (__f != __l && p != __f) {
            const_iterator __lm1 = __f;
            while (__lm1.ptr->next_ != __l.ptr)
                ++__lm1;
            if (__f != __lm1) {
                __lm1.ptr->next_ = p.ptr->next_;
                p.ptr->next_ = __f.ptr->next_;
                __f.ptr->next_ = __l.ptr;
            }
        }
    }

    template<class T, class Allocator>
    inline
    void
    forward_list<T, Allocator>::splice_after(const_iterator p,
                                             forward_list&& __x) {
        splice_after(p, __x);
    }

    template<class T, class Allocator>
    inline
    void
    forward_list<T, Allocator>::splice_after(const_iterator p,
                                             forward_list&& __x,
                                             const_iterator __i) {
        splice_after(p, __x, __i);
    }

    template<class T, class Allocator>
    inline
    void
    forward_list<T, Allocator>::splice_after(const_iterator p,
                                             forward_list&& __x,
                                             const_iterator __f, const_iterator __l) {
        splice_after(p, __x, __f, __l);
    }

    template<class T, class Allocator>
    void
    forward_list<T, Allocator>::remove(const value_type& __v) {
        forward_list<T, Allocator> __deleted_nodes; // collect the nodes we're removing
        iterator __e = end();
        for (iterator __i = before_begin(); __i.ptr->next_ != nullptr;) {
            if (__i.ptr->next_->value == __v) {
                iterator __j = std::next(__i, 2);
                for (; __j != __e && *__j == __v; ++__j);
                __deleted_nodes.splice_after(__deleted_nodes.before_begin(), *this, __i, __j);
                if (__j == __e)
                    break;
                __i = __j;
            }
            else
                ++__i;
        }
    }

    template<class T, class Allocator>
    template<class _Predicate>
    void
    forward_list<T, Allocator>::remove_if(_Predicate pred) {
        iterator __e = end();
        for (iterator __i = before_begin(); __i.ptr->next_ != nullptr;) {
            if (pred(__i.ptr->next_->value)) {
                iterator __j = std::next(__i, 2);
                for (; __j != __e && pred(*__j); ++__j);
                erase_after(__i, __j);
                if (__j == __e)
                    break;
                __i = __j;
            }
            else
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
            if (__i.ptr->next_ != __j.ptr)
                erase_after(__i, __j);
            __i = __j;
        }
    }

    template<class T, class Allocator>
    template<class _Compare>
    void
    forward_list<T, Allocator>::merge(forward_list& __x, _Compare __comp) {
        if (this != &__x) {
            base::before_begin()->next_ = merge(base::before_begin()->next_,
                                                __x.before_begin()->next_,
                                                __comp);
            __x.before_begin()->next_ = nullptr;
        }
    }

    template<class T, class Allocator>
    template<class _Compare>
    typename forward_list<T, Allocator>::node_pointer
    forward_list<T, Allocator>::merge(node_pointer __f1, node_pointer __f2,
                                      _Compare& __comp) {
        if (__f1 == nullptr)
            return __f2;
        if (__f2 == nullptr)
            return __f1;
        node_pointer __r;
        if (__comp(__f2->value, __f1->value)) {
            node_pointer __t = __f2;
            while (__t->next_ != nullptr &&
                   __comp(__t->next_->value, __f1->value))
                __t = __t->next_;
            __r = __f2;
            __f2 = __t->next_;
            __t->next_ = __f1;
        }
        else
            __r = __f1;
        node_pointer p = __f1;
        __f1 = __f1->next_;
        while (__f1 != nullptr && __f2 != nullptr) {
            if (__comp(__f2->value, __f1->value)) {
                node_pointer __t = __f2;
                while (__t->next_ != nullptr &&
                       __comp(__t->next_->value, __f1->value))
                    __t = __t->next_;
                p->next_ = __f2;
                __f2 = __t->next_;
                __t->next_ = __f1;
            }
            p = __f1;
            __f1 = __f1->next_;
        }
        if (__f2 != nullptr)
            p->next_ = __f2;
        return __r;
    }

    template<class T, class Allocator>
    template<class _Compare>
    inline
    void
    forward_list<T, Allocator>::sort(_Compare __comp) {
        base::before_begin()->next_ = sort(base::before_begin()->next_,
                                           std::distance(begin(), end()), __comp);
    }

    template<class T, class Allocator>
    template<class _Compare>
    typename forward_list<T, Allocator>::node_pointer
    forward_list<T, Allocator>::sort(node_pointer __f1, difference_type __sz,
                                     _Compare& __comp) {
        switch (__sz) {
            case 0:
            case 1:
                return __f1;
            case 2:
                if (__comp(__f1->next_->value, __f1->value)) {
                    node_pointer __t = __f1->next_;
                    __t->next_ = __f1;
                    __f1->next_ = nullptr;
                    __f1 = __t;
                }
                return __f1;
        }
        difference_type __sz1 = __sz / 2;
        difference_type __sz2 = __sz - __sz1;
        node_pointer __t = std::next(iterator(__f1), __sz1 - 1).ptr;
        node_pointer __f2 = __t->next;
        __t->next = nullptr;
        return merge(sort(__f1, __sz1, __comp),
                     sort(__f2, __sz2, __comp), __comp);
    }

    template<class T, class Allocator>
    void
    forward_list<T, Allocator>::reverse() noexcept {
        node_pointer p = base::before_begin()->next;
        if (p != nullptr) {
            node_pointer __f = p->next;
            p->next = nullptr;
            while (__f != nullptr) {
                node_pointer __t = __f->next;
                __f->next = p;
                p = __f;
                __f = __t;
            }
            base::before_begin()->next = p;
        }
    }

    template<class T, class Allocator>
    bool operator==(const forward_list<T, Allocator>& __x,
                    const forward_list<T, Allocator>& __y) {
        typedef forward_list<T, Allocator> _Cp;
        typedef typename _Cp::const_iterator _Ip;
        _Ip __ix = __x.begin();
        _Ip __ex = __x.end();
        _Ip __iy = __y.begin();
        _Ip __ey = __y.end();
        for (; __ix != __ex && __iy != __ey; ++__ix, ++__iy)
            if (!(*__ix == *__iy))
                return false;
        return (__ix == __ex) == (__iy == __ey);
    }


    template<class T, class Allocator>
    inline bool operator==(const forward_list<T, Allocator>& x,
                           const forward_list<T, Allocator>& y) {
        return x == y;
    }

    template<class T, class Allocator>
    inline bool operator!=(const forward_list<T, Allocator>& x,
                           const forward_list<T, Allocator>& y) {
        return !(x == y);
    }

    template<class T, class Allocator>
    inline bool operator<(const forward_list<T, Allocator>& x,
                          const forward_list<T, Allocator>& y) {
        return std::lexicographical_compare(x.begin(), x.end(),
                                            y.begin(), y.end());
    }

    template<class T, class Allocator>
    inline bool operator>(const forward_list<T, Allocator>& x,
                          const forward_list<T, Allocator>& y) {
        return y < x;
    }

    template<class T, class Allocator>
    inline bool operator>=(const forward_list<T, Allocator>& x,
                           const forward_list<T, Allocator>& y) {
        return !(x < y);
    }

    template<class T, class Allocator>
    inline bool operator<=(const forward_list<T, Allocator>& x,
                           const forward_list<T, Allocator>& y) {
        return !(y < x);
    }

    template<class T, class Allocator>
    inline void swap(forward_list<T, Allocator>& x, forward_list<T, Allocator>& y)
    noexcept(noexcept(x.swap(y))) {
        x.swap(y);
    }

};

#endif //ALGORITHMS_FORWARD_LIST_H












