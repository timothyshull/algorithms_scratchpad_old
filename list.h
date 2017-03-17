//
// Created by Timothy Shull on 2/7/16.
//

#ifndef ALGORITHMS_LIST_H
#define ALGORITHMS_LIST_H

#endif //ALGORITHMS_LIST_H


// -*- C++ -*-
//===----------------------- forward_list ---------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_FORWARD_LIST
#define _LIBCPP_FORWARD_LIST

/*
    forward_list synopsis

namespace std
{

template <class T, class Allocator = allocator<T>>
class forward_list
{
public:
    typedef T         value_type;
    typedef Allocator allocator_type;

    typedef value_type&                                                reference;
    typedef const value_type&                                          const_reference;
    typedef typename allocator_traits<allocator_type>::pointer         pointer;
    typedef typename allocator_traits<allocator_type>::const_pointer   const_pointer;
    typedef typename allocator_traits<allocator_type>::size_type       size_type;
    typedef typename allocator_traits<allocator_type>::difference_type difference_type;

    typedef <details> iterator;
    typedef <details> const_iterator;

    forward_list()
        noexcept(is_nothrow_default_constructible<allocator_type>::value);
    explicit forward_list(const allocator_type& a);
    explicit forward_list(size_type n);
    explicit forward_list(size_type n, const allocator_type& a); // C++14
    forward_list(size_type n, const value_type& v);
    forward_list(size_type n, const value_type& v, const allocator_type& a);
    template <class InputIterator>
        forward_list(InputIterator first, InputIterator last);
    template <class InputIterator>
        forward_list(InputIterator first, InputIterator last, const allocator_type& a);
    forward_list(const forward_list& x);
    forward_list(const forward_list& x, const allocator_type& a);
    forward_list(forward_list&& x)
        noexcept(is_nothrow_move_constructible<allocator_type>::value);
    forward_list(forward_list&& x, const allocator_type& a);
    forward_list(initializer_list<value_type> il);
    forward_list(initializer_list<value_type> il, const allocator_type& a);

    ~forward_list();

    forward_list& operator=(const forward_list& x);
    forward_list& operator=(forward_list&& x)
        noexcept(
             allocator_type::propagate_on_container_move_assignment::value &&
             is_nothrow_move_assignable<allocator_type>::value);
    forward_list& operator=(initializer_list<value_type> il);

    template <class InputIterator>
        void assign(InputIterator first, InputIterator last);
    void assign(size_type n, const value_type& v);
    void assign(initializer_list<value_type> il);

    allocator_type get_allocator() const noexcept;

    iterator       begin() noexcept;
    const_iterator begin() const noexcept;
    iterator       end() noexcept;
    const_iterator end() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    iterator       before_begin() noexcept;
    const_iterator before_begin() const noexcept;
    const_iterator cbefore_begin() const noexcept;

    bool empty() const noexcept;
    size_type max_size() const noexcept;

    reference       front();
    const_reference front() const;

    template <class... Args> void emplace_front(Args&&... args);
    void push_front(const value_type& v);
    void push_front(value_type&& v);

    void pop_front();

    template <class... Args>
        iterator emplace_after(const_iterator p, Args&&... args);
    iterator insert_after(const_iterator p, const value_type& v);
    iterator insert_after(const_iterator p, value_type&& v);
    iterator insert_after(const_iterator p, size_type n, const value_type& v);
    template <class InputIterator>
        iterator insert_after(const_iterator p,
                              InputIterator first, InputIterator last);
    iterator insert_after(const_iterator p, initializer_list<value_type> il);

    iterator erase_after(const_iterator p);
    iterator erase_after(const_iterator first, const_iterator last);

    void swap(forward_list& x)
        noexcept(!allocator_type::propagate_on_container_swap::value ||
                 __is_nothrow_swappable<allocator_type>::value);

    void resize(size_type n);
    void resize(size_type n, const value_type& v);
    void clear() noexcept;

    void splice_after(const_iterator p, forward_list& x);
    void splice_after(const_iterator p, forward_list&& x);
    void splice_after(const_iterator p, forward_list& x, const_iterator i);
    void splice_after(const_iterator p, forward_list&& x, const_iterator i);
    void splice_after(const_iterator p, forward_list& x,
                      const_iterator first, const_iterator last);
    void splice_after(const_iterator p, forward_list&& x,
                      const_iterator first, const_iterator last);
    void remove(const value_type& v);
    template <class Predicate> void remove_if(Predicate pred);
    void unique();
    template <class BinaryPredicate> void unique(BinaryPredicate binary_pred);
    void merge(forward_list& x);
    void merge(forward_list&& x);
    template <class Compare> void merge(forward_list& x, Compare comp);
    template <class Compare> void merge(forward_list&& x, Compare comp);
    void sort();
    template <class Compare> void sort(Compare comp);
    void reverse() noexcept;
};

template <class T, class Allocator>
    bool operator==(const forward_list<T, Allocator>& x,
                    const forward_list<T, Allocator>& y);

template <class T, class Allocator>
    bool operator< (const forward_list<T, Allocator>& x,
                    const forward_list<T, Allocator>& y);

template <class T, class Allocator>
    bool operator!=(const forward_list<T, Allocator>& x,
                    const forward_list<T, Allocator>& y);

template <class T, class Allocator>
    bool operator> (const forward_list<T, Allocator>& x,
                    const forward_list<T, Allocator>& y);

template <class T, class Allocator>
    bool operator>=(const forward_list<T, Allocator>& x,
                    const forward_list<T, Allocator>& y);

template <class T, class Allocator>
    bool operator<=(const forward_list<T, Allocator>& x,
                    const forward_list<T, Allocator>& y);

template <class T, class Allocator>
    void swap(forward_list<T, Allocator>& x, forward_list<T, Allocator>& y)
         noexcept(noexcept(x.swap(y)));

}  // std

*/

#include <__config>

#include <initializer_list>
#include <memory>
#include <limits>
#include <iterator>
#include <algorithm>

#include <__undef_min_max>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

        template<class _Tp, class _VoidPtr>
        struct __forward_list_node;

        template<class _NodePtr>
        struct __forward_begin_node {
            typedef _NodePtr pointer;

            pointer __next_;

            _LIBCPP_INLINE_VISIBILITY __forward_begin_node() : __next_(nullptr) { }
        };

        template<class _Tp, class _VoidPtr>
        struct _LIBCPP_HIDDEN __begin_node_of {
            typedef __forward_begin_node
                    <
                            typename pointer_traits<_VoidPtr>::template
#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
                            rebind<__forward_list_node<_Tp, _VoidPtr> >
#else
                    rebind<__forward_list_node<_Tp, _VoidPtr> >::other
#endif
            > type;
        };

        template<class _Tp, class _VoidPtr>
        struct __forward_list_node
                : public __begin_node_of<_Tp, _VoidPtr>::type {
            typedef _Tp value_type;

            value_type __value_;
        };

        template<class _Tp, class _Alloc = allocator<_Tp> >
        class _LIBCPP_TYPE_VIS_ONLY forward_list;

        template<class _NodeConstPtr>
        class _LIBCPP_TYPE_VIS_ONLY __forward_list_const_iterator;

        template<class _NodePtr>
        class _LIBCPP_TYPE_VIS_ONLY __forward_list_iterator {
            typedef _NodePtr __node_pointer;

            __node_pointer __ptr_;

            _LIBCPP_INLINE_VISIBILITY
            explicit __forward_list_iterator(__node_pointer __p) _NOEXCEPT : __ptr_(__p) { }

            template<class, class> friend
            class _LIBCPP_TYPE_VIS_ONLY forward_list;

            template<class> friend
            class _LIBCPP_TYPE_VIS_ONLY __forward_list_const_iterator;

        public:
            typedef forward_iterator_tag iterator_category;
            typedef typename pointer_traits<__node_pointer>::element_type::value_type
                    value_type;
            typedef value_type& reference;
            typedef typename pointer_traits<__node_pointer>::difference_type
                    difference_type;
            typedef typename pointer_traits<__node_pointer>::template
#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            rebind<value_type>
#else
            rebind<value_type>::other
#endif
                    pointer;

            _LIBCPP_INLINE_VISIBILITY
            __forward_list_iterator() _NOEXCEPT : __ptr_(nullptr) { }

            _LIBCPP_INLINE_VISIBILITY
            reference operator*() const { return __ptr_->__value_; }

            _LIBCPP_INLINE_VISIBILITY
            pointer operator->() const { return pointer_traits<pointer>::pointer_to(__ptr_->__value_); }

            _LIBCPP_INLINE_VISIBILITY
            __forward_list_iterator& operator++() {
                __ptr_ = __ptr_->__next_;
                return *this;
            }

            _LIBCPP_INLINE_VISIBILITY
            __forward_list_iterator operator++(int) {
                __forward_list_iterator __t(*this);
                ++(*this);
                return __t;
            }

            friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const __forward_list_iterator& __x,
                            const __forward_list_iterator& __y) { return __x.__ptr_ == __y.__ptr_; }

            friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const __forward_list_iterator& __x,
                            const __forward_list_iterator& __y) { return !(__x == __y); }
        };

        template<class _NodeConstPtr>
        class _LIBCPP_TYPE_VIS_ONLY __forward_list_const_iterator {
            typedef _NodeConstPtr __node_const_pointer;

            __node_const_pointer __ptr_;

            _LIBCPP_INLINE_VISIBILITY
            explicit __forward_list_const_iterator(__node_const_pointer __p) _NOEXCEPT
                    : __ptr_(__p) { }

            typedef typename remove_const
                    <
                            typename pointer_traits<__node_const_pointer>::element_type
                    >::type __node;
            typedef typename pointer_traits<__node_const_pointer>::template
#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            rebind<__node>
#else
            rebind<__node>::other
#endif
                    __node_pointer;

            template<class, class> friend
            class forward_list;

        public:
            typedef forward_iterator_tag iterator_category;
            typedef typename __node::value_type value_type;
            typedef const value_type& reference;
            typedef typename pointer_traits<__node_const_pointer>::difference_type
                    difference_type;
            typedef typename pointer_traits<__node_const_pointer>::template
#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            rebind<const value_type>
#else
            rebind<const value_type>::other
#endif
                    pointer;

            _LIBCPP_INLINE_VISIBILITY
            __forward_list_const_iterator() _NOEXCEPT : __ptr_(nullptr) { }

            _LIBCPP_INLINE_VISIBILITY
            __forward_list_const_iterator(__forward_list_iterator<__node_pointer> __p) _NOEXCEPT
                    : __ptr_(__p.__ptr_) { }

            _LIBCPP_INLINE_VISIBILITY
            reference operator*() const { return __ptr_->__value_; }

            _LIBCPP_INLINE_VISIBILITY
            pointer operator->() const { return pointer_traits<pointer>::pointer_to(__ptr_->__value_); }

            _LIBCPP_INLINE_VISIBILITY
            __forward_list_const_iterator& operator++() {
                __ptr_ = __ptr_->__next_;
                return *this;
            }

            _LIBCPP_INLINE_VISIBILITY
            __forward_list_const_iterator operator++(int) {
                __forward_list_const_iterator __t(*this);
                ++(*this);
                return __t;
            }

            friend _LIBCPP_INLINE_VISIBILITY
            bool operator==(const __forward_list_const_iterator& __x,
                            const __forward_list_const_iterator& __y) { return __x.__ptr_ == __y.__ptr_; }

            friend _LIBCPP_INLINE_VISIBILITY
            bool operator!=(const __forward_list_const_iterator& __x,
                            const __forward_list_const_iterator& __y) { return !(__x == __y); }
        };

        template<class _Tp, class _Alloc>
        class __forward_list_base {
        protected:
            typedef _Tp value_type;
            typedef _Alloc allocator_type;

            typedef typename allocator_traits<allocator_type>::void_pointer void_pointer;
            typedef __forward_list_node<value_type, void_pointer> __node;
            typedef typename __begin_node_of<value_type, void_pointer>::type __begin_node;
            typedef typename allocator_traits<allocator_type>::template
#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            rebind_alloc<__node>
#else
            rebind_alloc<__node>::other
#endif
                    __node_allocator;
            typedef allocator_traits<__node_allocator> __node_traits;
            typedef typename __node_traits::pointer __node_pointer;
            typedef typename __node_traits::pointer __node_const_pointer;

            typedef typename allocator_traits<allocator_type>::template
#ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
            rebind_alloc<__begin_node>
#else
            rebind_alloc<__begin_node>::other
#endif
                    __begin_node_allocator;
            typedef typename allocator_traits<__begin_node_allocator>::pointer __begin_node_pointer;

            __compressed_pair<__begin_node, __node_allocator> __before_begin_;

            _LIBCPP_INLINE_VISIBILITY
            __node_pointer __before_begin() _NOEXCEPT {
                return static_cast<__node_pointer>(pointer_traits<__begin_node_pointer>::
                pointer_to(__before_begin_.first()));
            }

            _LIBCPP_INLINE_VISIBILITY
            __node_const_pointer __before_begin() const _NOEXCEPT {
                return static_cast<__node_const_pointer>(pointer_traits<__begin_node_pointer>::
                pointer_to(const_cast<__begin_node&>(__before_begin_.first())));
            }

            _LIBCPP_INLINE_VISIBILITY
            __node_allocator& __alloc() _NOEXCEPT { return __before_begin_.second(); }

            _LIBCPP_INLINE_VISIBILITY
            const __node_allocator& __alloc() const _NOEXCEPT { return __before_begin_.second(); }

            typedef __forward_list_iterator<__node_pointer> iterator;
            typedef __forward_list_const_iterator<__node_pointer> const_iterator;

            _LIBCPP_INLINE_VISIBILITY
            __forward_list_base()
            _NOEXCEPT_(is_nothrow_default_constructible<__node_allocator>::value)
                    : __before_begin_(__begin_node()) { }

            _LIBCPP_INLINE_VISIBILITY
            __forward_list_base(const allocator_type& __a)
                    : __before_begin_(__begin_node(), __node_allocator(__a)) { }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
        public:
            __forward_list_base(__forward_list_base&& __x)
            _NOEXCEPT_(is_nothrow_move_constructible<__node_allocator>::value);

            __forward_list_base(__forward_list_base&& __x, const allocator_type& __a);

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

        private:
            __forward_list_base(const __forward_list_base&);

            __forward_list_base& operator=(const __forward_list_base&);

        public:
            ~__forward_list_base();

        protected:
            _LIBCPP_INLINE_VISIBILITY
            void __copy_assign_alloc(const __forward_list_base& __x) {
                __copy_assign_alloc(__x, integral_constant<bool,
                        __node_traits::propagate_on_container_copy_assignment::value>());
            }

            _LIBCPP_INLINE_VISIBILITY
            void __move_assign_alloc(__forward_list_base& __x)
            _NOEXCEPT_(!__node_traits::propagate_on_container_move_assignment::value ||
                       is_nothrow_move_assignable<__node_allocator>::value) {
                __move_assign_alloc(__x, integral_constant<bool,
                        __node_traits::propagate_on_container_move_assignment::value>());
            }

        public:
            void swap(__forward_list_base& __x)
                    _NOEXCEPT_(!__node_traits::propagate_on_container_swap::value ||
                               __is_nothrow_swappable<__node_allocator>::value);

        protected:
            void clear() _NOEXCEPT;

        private:
            _LIBCPP_INLINE_VISIBILITY
            void __copy_assign_alloc(const __forward_list_base&, false_type) { }

            _LIBCPP_INLINE_VISIBILITY
            void __copy_assign_alloc(const __forward_list_base& __x, true_type) {
                if (__alloc() != __x.__alloc())
                    clear();
                __alloc() = __x.__alloc();
            }

            _LIBCPP_INLINE_VISIBILITY
            void __move_assign_alloc(__forward_list_base& __x, false_type) _NOEXCEPT { }

            _LIBCPP_INLINE_VISIBILITY
            void __move_assign_alloc(__forward_list_base& __x, true_type)
            _NOEXCEPT_(is_nothrow_move_assignable<__node_allocator>::value) { __alloc() = _VSTD::move(__x.__alloc()); }

            _LIBCPP_INLINE_VISIBILITY
            static void __swap_alloc(__node_allocator& __x, __node_allocator& __y)
            _NOEXCEPT_(!__node_traits::propagate_on_container_swap::value ||
                       __is_nothrow_swappable<__node_allocator>::value) {
                __swap_alloc(__x, __y, integral_constant<bool,
                        __node_traits::propagate_on_container_swap::value>());
            }

            _LIBCPP_INLINE_VISIBILITY
            static void __swap_alloc(__node_allocator& __x, __node_allocator& __y,
                                     false_type)
            _NOEXCEPT { }

            _LIBCPP_INLINE_VISIBILITY
            static void __swap_alloc(__node_allocator& __x, __node_allocator& __y,
                                     true_type)
            _NOEXCEPT_(__is_nothrow_swappable<__node_allocator>::value) {
                using _VSTD::swap;
                swap(__x, __y);
            }
        };

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

        template<class _Tp, class _Alloc>
        inline _LIBCPP_INLINE_VISIBILITY
        __forward_list_base<_Tp, _Alloc>::__forward_list_base(__forward_list_base&& __x)
        _NOEXCEPT_(is_nothrow_move_constructible<__node_allocator>::value)
                : __before_begin_(_VSTD::move(__x.__before_begin_)) {
            __x.__before_begin()->__next_ = nullptr;
        }

        template<class _Tp, class _Alloc>
        inline _LIBCPP_INLINE_VISIBILITY
        __forward_list_base<_Tp, _Alloc>::__forward_list_base(__forward_list_base&& __x,
                                                              const allocator_type& __a)
                : __before_begin_(__begin_node(), __node_allocator(__a)) {
            if (__alloc() == __x.__alloc()) {
                __before_begin()->__next_ = __x.__before_begin()->__next_;
                __x.__before_begin()->__next_ = nullptr;
            }
        }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

        template<class _Tp, class _Alloc>
        __forward_list_base<_Tp, _Alloc>::~__forward_list_base() {
            clear();
        }

        template<class _Tp, class _Alloc>
        inline _LIBCPP_INLINE_VISIBILITY
        void
        __forward_list_base<_Tp, _Alloc>::swap(__forward_list_base& __x)
        _NOEXCEPT_(!__node_traits::propagate_on_container_swap::value ||
                   __is_nothrow_swappable<__node_allocator>::value) {
            __swap_alloc(__alloc(), __x.__alloc());
            using _VSTD::swap;
            swap(__before_begin()->__next_, __x.__before_begin()->__next_);
        }

        template<class _Tp, class _Alloc>
        void
        __forward_list_base<_Tp, _Alloc>::clear() _NOEXCEPT {
            __node_allocator& __a = __alloc();
            for (__node_pointer __p = __before_begin()->__next_; __p != nullptr;) {
                __node_pointer __next = __p->__next_;
                __node_traits::destroy(__a, _VSTD::addressof(__p->__value_));
                __node_traits::deallocate(__a, __p, 1);
                __p = __next;
            }
            __before_begin()->__next_ = nullptr;
        }

        template<class _Tp, class _Alloc /*= allocator<_Tp>*/>
        class _LIBCPP_TYPE_VIS_ONLY forward_list
                : private __forward_list_base<_Tp, _Alloc> {
            typedef __forward_list_base<_Tp, _Alloc> base;
            typedef typename base::__node_allocator __node_allocator;
            typedef typename base::__node __node;
            typedef typename base::__node_traits __node_traits;
            typedef typename base::__node_pointer __node_pointer;

        public:
            typedef _Tp value_type;
            typedef _Alloc allocator_type;

            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef typename allocator_traits<allocator_type>::pointer pointer;
            typedef typename allocator_traits<allocator_type>::const_pointer const_pointer;
            typedef typename allocator_traits<allocator_type>::size_type size_type;
            typedef typename allocator_traits<allocator_type>::difference_type difference_type;

            typedef typename base::iterator iterator;
            typedef typename base::const_iterator const_iterator;

            _LIBCPP_INLINE_VISIBILITY
            forward_list()
            _NOEXCEPT_(is_nothrow_default_constructible<__node_allocator>::value) { } // = default;
            explicit forward_list(const allocator_type& __a);

            explicit forward_list(size_type __n);

#if _LIBCPP_STD_VER > 11
            explicit forward_list(size_type __n, const allocator_type& __a);
#endif

            forward_list(size_type __n, const value_type& __v);

            forward_list(size_type __n, const value_type& __v, const allocator_type& __a);

            template<class _InputIterator>
            forward_list(_InputIterator __f, _InputIterator __l,
                         typename enable_if<
                                 __is_input_iterator<_InputIterator>::value
                         >::type* = nullptr);

            template<class _InputIterator>
            forward_list(_InputIterator __f, _InputIterator __l,
                         const allocator_type& __a,
                         typename enable_if<
                                 __is_input_iterator<_InputIterator>::value
                         >::type* = nullptr);

            forward_list(const forward_list& __x);

            forward_list(const forward_list& __x, const allocator_type& __a);

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

            _LIBCPP_INLINE_VISIBILITY
            forward_list(forward_list&& __x)
            _NOEXCEPT_(is_nothrow_move_constructible<base>::value)
                    : base(_VSTD::move(__x)) { }

            forward_list(forward_list&& __x, const allocator_type& __a);

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#ifndef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

            forward_list(initializer_list<value_type> __il);

            forward_list(initializer_list<value_type> __il, const allocator_type& __a);

#endif  // _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

            // ~forward_list() = default;

            forward_list& operator=(const forward_list& __x);

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

            forward_list& operator=(forward_list&& __x)
                    _NOEXCEPT_(
                            __node_traits::propagate_on_container_move_assignment::value &&
                            is_nothrow_move_assignable<allocator_type>::value);

#endif
#ifndef  _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

            forward_list& operator=(initializer_list<value_type> __il);

#endif  // _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

            template<class _InputIterator>
            typename enable_if
                    <
                            __is_input_iterator<_InputIterator>::value,
                            void
                    >::type
                    assign(_InputIterator __f, _InputIterator __l);

            void assign(size_type __n, const value_type& __v);

#ifndef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

            void assign(initializer_list<value_type> __il);

#endif  // _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

            _LIBCPP_INLINE_VISIBILITY
            allocator_type get_allocator() const _NOEXCEPT { return allocator_type(base::__alloc()); }

            _LIBCPP_INLINE_VISIBILITY
            iterator begin() _NOEXCEPT { return iterator(base::__before_begin()->__next_); }

            _LIBCPP_INLINE_VISIBILITY
            const_iterator begin() const _NOEXCEPT { return const_iterator(base::__before_begin()->__next_); }

            _LIBCPP_INLINE_VISIBILITY
            iterator end() _NOEXCEPT { return iterator(nullptr); }

            _LIBCPP_INLINE_VISIBILITY
            const_iterator end() const _NOEXCEPT { return const_iterator(nullptr); }

            _LIBCPP_INLINE_VISIBILITY
            const_iterator cbegin() const _NOEXCEPT { return const_iterator(base::__before_begin()->__next_); }

            _LIBCPP_INLINE_VISIBILITY
            const_iterator cend() const _NOEXCEPT { return const_iterator(nullptr); }

            _LIBCPP_INLINE_VISIBILITY
            iterator before_begin() _NOEXCEPT { return iterator(base::__before_begin()); }

            _LIBCPP_INLINE_VISIBILITY
            const_iterator before_begin() const _NOEXCEPT { return const_iterator(base::__before_begin()); }

            _LIBCPP_INLINE_VISIBILITY
            const_iterator cbefore_begin() const _NOEXCEPT { return const_iterator(base::__before_begin()); }

            _LIBCPP_INLINE_VISIBILITY
            bool empty() const _NOEXCEPT { return base::__before_begin()->__next_ == nullptr; }

            _LIBCPP_INLINE_VISIBILITY
            size_type max_size() const _NOEXCEPT { return numeric_limits<size_type>::max(); }

            _LIBCPP_INLINE_VISIBILITY
            reference front() { return base::__before_begin()->__next_->__value_; }

            _LIBCPP_INLINE_VISIBILITY
            const_reference front() const { return base::__before_begin()->__next_->__value_; }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
#ifndef _LIBCPP_HAS_NO_VARIADICS

            template<class... _Args>
            void emplace_front(_Args&& ... __args);

#endif

            void push_front(value_type&& __v);

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

            void push_front(const value_type& __v);

            void pop_front();

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
#ifndef _LIBCPP_HAS_NO_VARIADICS

            template<class... _Args>
            iterator emplace_after(const_iterator __p, _Args&& ... __args);

#endif  // _LIBCPP_HAS_NO_VARIADICS

            iterator insert_after(const_iterator __p, value_type&& __v);

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

            iterator insert_after(const_iterator __p, const value_type& __v);

            iterator insert_after(const_iterator __p, size_type __n, const value_type& __v);

            template<class _InputIterator>
            _LIBCPP_INLINE_VISIBILITY
            typename enable_if
                    <
                            __is_input_iterator<_InputIterator>::value,
                            iterator
                    >::type
                    insert_after(const_iterator __p, _InputIterator __f, _InputIterator __l);

#ifndef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

            iterator insert_after(const_iterator __p, initializer_list<value_type> __il) {
                return insert_after(__p, __il.begin(), __il.end());
            }

#endif  // _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

            iterator erase_after(const_iterator __p);

            iterator erase_after(const_iterator __f, const_iterator __l);

            _LIBCPP_INLINE_VISIBILITY
            void swap(forward_list& __x)
            _NOEXCEPT_(!__node_traits::propagate_on_container_swap::value ||
                       __is_nothrow_swappable<__node_allocator>::value) { base::swap(__x); }

            void resize(size_type __n);

            void resize(size_type __n, const value_type& __v);

            _LIBCPP_INLINE_VISIBILITY
            void clear() _NOEXCEPT { base::clear(); }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

            _LIBCPP_INLINE_VISIBILITY
            void splice_after(const_iterator __p, forward_list&& __x);

            _LIBCPP_INLINE_VISIBILITY
            void splice_after(const_iterator __p, forward_list&& __x, const_iterator __i);

            _LIBCPP_INLINE_VISIBILITY
            void splice_after(const_iterator __p, forward_list&& __x,
                              const_iterator __f, const_iterator __l);

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

            void splice_after(const_iterator __p, forward_list& __x);

            void splice_after(const_iterator __p, forward_list& __x, const_iterator __i);

            void splice_after(const_iterator __p, forward_list& __x,
                              const_iterator __f, const_iterator __l);

            void remove(const value_type& __v);

            template<class _Predicate>
            void remove_if(_Predicate __pred);

            _LIBCPP_INLINE_VISIBILITY
            void unique() { unique(__equal_to<value_type>()); }

            template<class _BinaryPredicate>
            void unique(_BinaryPredicate __binary_pred);

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

            _LIBCPP_INLINE_VISIBILITY
            void merge(forward_list&& __x) { merge(__x, __less<value_type>()); }

            template<class _Compare>
            _LIBCPP_INLINE_VISIBILITY
            void merge(forward_list&& __x, _Compare __comp) { merge(__x, _VSTD::move(__comp)); }
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

            _LIBCPP_INLINE_VISIBILITY
            void merge(forward_list& __x) { merge(__x, __less<value_type>()); }

            template<class _Compare>
            void merge(forward_list& __x, _Compare __comp);

            _LIBCPP_INLINE_VISIBILITY
            void sort() { sort(__less<value_type>()); }

            template<class _Compare>
            void sort(_Compare __comp);

            void reverse() _NOEXCEPT;

        private:

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

            void __move_assign(forward_list& __x, true_type)
                    _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value);

            void __move_assign(forward_list& __x, false_type);

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

            template<class _Compare>
            static
            __node_pointer
                    __merge(__node_pointer __f1, __node_pointer __f2, _Compare& __comp);

            template<class _Compare>
            static
            __node_pointer
                    __sort(__node_pointer __f, difference_type __sz, _Compare& __comp);
        };

        template<class _Tp, class _Alloc>
        inline _LIBCPP_INLINE_VISIBILITY
        forward_list<_Tp, _Alloc>::forward_list(const allocator_type& __a)
                : base(__a) {
        }

        template<class _Tp, class _Alloc>
        forward_list<_Tp, _Alloc>::forward_list(size_type __n) {
            if (__n > 0) {
                __node_allocator& __a = base::__alloc();
                typedef __allocator_destructor<__node_allocator> _Dp;
                unique_ptr<__node, _Dp> __h(nullptr, _Dp(__a, 1));
                for (__node_pointer __p = base::__before_begin(); __n > 0; --__n,
                        __p = __p->__next_) {
                    __h.reset(__node_traits::allocate(__a, 1));
                    __node_traits::construct(__a, _VSTD::addressof(__h->__value_));
                    __h->__next_ = nullptr;
                    __p->__next_ = __h.release();
                }
            }
        }

#if _LIBCPP_STD_VER > 11
        template <class _Tp, class _Alloc>
forward_list<_Tp, _Alloc>::forward_list(size_type __n, const allocator_type& __a)
    : base ( __a )
{
    if (__n > 0)
    {
        __node_allocator& __a = base::__alloc();
        typedef __allocator_destructor<__node_allocator> _Dp;
        unique_ptr<__node, _Dp> __h(nullptr, _Dp(__a, 1));
        for (__node_pointer __p = base::__before_begin(); __n > 0; --__n,
                                                             __p = __p->__next_)
        {
            __h.reset(__node_traits::allocate(__a, 1));
            __node_traits::construct(__a, _VSTD::addressof(__h->__value_));
            __h->__next_ = nullptr;
            __p->__next_ = __h.release();
        }
    }
}
#endif

        template<class _Tp, class _Alloc>
        forward_list<_Tp, _Alloc>::forward_list(size_type __n, const value_type& __v) {
            insert_after(cbefore_begin(), __n, __v);
        }

        template<class _Tp, class _Alloc>
        forward_list<_Tp, _Alloc>::forward_list(size_type __n, const value_type& __v,
                                                const allocator_type& __a)
                : base(__a) {
            insert_after(cbefore_begin(), __n, __v);
        }

        template<class _Tp, class _Alloc>
        template<class _InputIterator>
        forward_list<_Tp, _Alloc>::forward_list(_InputIterator __f, _InputIterator __l,
                                                typename enable_if<
                                                        __is_input_iterator<_InputIterator>::value
                                                >::type*) {
            insert_after(cbefore_begin(), __f, __l);
        }

        template<class _Tp, class _Alloc>
        template<class _InputIterator>
        forward_list<_Tp, _Alloc>::forward_list(_InputIterator __f, _InputIterator __l,
                                                const allocator_type& __a,
                                                typename enable_if<
                                                        __is_input_iterator<_InputIterator>::value
                                                >::type*)
                : base(__a) {
            insert_after(cbefore_begin(), __f, __l);
        }

        template<class _Tp, class _Alloc>
        forward_list<_Tp, _Alloc>::forward_list(const forward_list& __x)
                : base(allocator_type(
                __node_traits::select_on_container_copy_construction(__x.__alloc())
        )
        ) {
            insert_after(cbefore_begin(), __x.begin(), __x.end());
        }

        template<class _Tp, class _Alloc>
        forward_list<_Tp, _Alloc>::forward_list(const forward_list& __x,
                                                const allocator_type& __a)
                : base(__a) {
            insert_after(cbefore_begin(), __x.begin(), __x.end());
        }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

        template<class _Tp, class _Alloc>
        forward_list<_Tp, _Alloc>::forward_list(forward_list&& __x,
                                                const allocator_type& __a)
                : base(_VSTD::move(__x), __a) {
            if (base::__alloc() != __x.__alloc()) {
                typedef move_iterator<iterator> _Ip;
                insert_after(cbefore_begin(), _Ip(__x.begin()), _Ip(__x.end()));
            }
        }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

#ifndef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

        template<class _Tp, class _Alloc>
        forward_list<_Tp, _Alloc>::forward_list(initializer_list<value_type> __il) {
            insert_after(cbefore_begin(), __il.begin(), __il.end());
        }

        template<class _Tp, class _Alloc>
        forward_list<_Tp, _Alloc>::forward_list(initializer_list<value_type> __il,
                                                const allocator_type& __a)
                : base(__a) {
            insert_after(cbefore_begin(), __il.begin(), __il.end());
        }

#endif  // _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

        template<class _Tp, class _Alloc>
        forward_list<_Tp, _Alloc>&
        forward_list<_Tp, _Alloc>::operator=(const forward_list& __x) {
            if (this != &__x) {
                base::__copy_assign_alloc(__x);
                assign(__x.begin(), __x.end());
            }
            return *this;
        }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

        template<class _Tp, class _Alloc>
        void
        forward_list<_Tp, _Alloc>::__move_assign(forward_list& __x, true_type)
        _NOEXCEPT_(is_nothrow_move_assignable<allocator_type>::value) {
            clear();
            base::__move_assign_alloc(__x);
            base::__before_begin()->__next_ = __x.__before_begin()->__next_;
            __x.__before_begin()->__next_ = nullptr;
        }

        template<class _Tp, class _Alloc>
        void
        forward_list<_Tp, _Alloc>::__move_assign(forward_list& __x, false_type) {
            if (base::__alloc() == __x.__alloc())
                __move_assign(__x, true_type());
            else {
                typedef move_iterator<iterator> _Ip;
                assign(_Ip(__x.begin()), _Ip(__x.end()));
            }
        }

        template<class _Tp, class _Alloc>
        inline _LIBCPP_INLINE_VISIBILITY
        forward_list<_Tp, _Alloc>&
        forward_list<_Tp, _Alloc>::operator=(forward_list&& __x)
        _NOEXCEPT_(
                __node_traits::propagate_on_container_move_assignment::value &&
                is_nothrow_move_assignable<allocator_type>::value) {
            __move_assign(__x, integral_constant<bool,
                    __node_traits::propagate_on_container_move_assignment::value>());
            return *this;
        }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

#ifndef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

        template<class _Tp, class _Alloc>
        inline _LIBCPP_INLINE_VISIBILITY
        forward_list<_Tp, _Alloc>&
        forward_list<_Tp, _Alloc>::operator=(initializer_list<value_type> __il) {
            assign(__il.begin(), __il.end());
            return *this;
        }

#endif  // _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

        template<class _Tp, class _Alloc>
        template<class _InputIterator>
        typename enable_if
                <
                        __is_input_iterator<_InputIterator>::value,
                        void
                >::type
        forward_list<_Tp, _Alloc>::assign(_InputIterator __f, _InputIterator __l) {
            iterator __i = before_begin();
            iterator __j = _VSTD::next(__i);
            iterator __e = end();
            for (; __j != __e && __f != __l; ++__i, (void) ++__j, ++__f)
                *__j = *__f;
            if (__j == __e)
                insert_after(__i, __f, __l);
            else
                erase_after(__i, __e);
        }

        template<class _Tp, class _Alloc>
        void
        forward_list<_Tp, _Alloc>::assign(size_type __n, const value_type& __v) {
            iterator __i = before_begin();
            iterator __j = _VSTD::next(__i);
            iterator __e = end();
            for (; __j != __e && __n > 0; --__n, ++__i, ++__j)
                *__j = __v;
            if (__j == __e)
                insert_after(__i, __n, __v);
            else
                erase_after(__i, __e);
        }

#ifndef _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

        template<class _Tp, class _Alloc>
        inline _LIBCPP_INLINE_VISIBILITY
        void
        forward_list<_Tp, _Alloc>::assign(initializer_list<value_type> __il) {
            assign(__il.begin(), __il.end());
        }

#endif  // _LIBCPP_HAS_NO_GENERALIZED_INITIALIZERS

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
#ifndef _LIBCPP_HAS_NO_VARIADICS

        template<class _Tp, class _Alloc>
        template<class... _Args>
        void
        forward_list<_Tp, _Alloc>::emplace_front(_Args&& ... __args) {
            __node_allocator& __a = base::__alloc();
            typedef __allocator_destructor<__node_allocator> _Dp;
            unique_ptr<__node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
            __node_traits::construct(__a, _VSTD::addressof(__h->__value_),
                                     _VSTD::forward<_Args>(__args)...);
            __h->__next_ = base::__before_begin()->__next_;
            base::__before_begin()->__next_ = __h.release();
        }

#endif  // _LIBCPP_HAS_NO_VARIADICS

        template<class _Tp, class _Alloc>
        void
        forward_list<_Tp, _Alloc>::push_front(value_type&& __v) {
            __node_allocator& __a = base::__alloc();
            typedef __allocator_destructor<__node_allocator> _Dp;
            unique_ptr<__node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
            __node_traits::construct(__a, _VSTD::addressof(__h->__value_), _VSTD::move(__v));
            __h->__next_ = base::__before_begin()->__next_;
            base::__before_begin()->__next_ = __h.release();
        }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

        template<class _Tp, class _Alloc>
        void
        forward_list<_Tp, _Alloc>::push_front(const value_type& __v) {
            __node_allocator& __a = base::__alloc();
            typedef __allocator_destructor<__node_allocator> _Dp;
            unique_ptr<__node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
            __node_traits::construct(__a, _VSTD::addressof(__h->__value_), __v);
            __h->__next_ = base::__before_begin()->__next_;
            base::__before_begin()->__next_ = __h.release();
        }

        template<class _Tp, class _Alloc>
        void
        forward_list<_Tp, _Alloc>::pop_front() {
            __node_allocator& __a = base::__alloc();
            __node_pointer __p = base::__before_begin()->__next_;
            base::__before_begin()->__next_ = __p->__next_;
            __node_traits::destroy(__a, _VSTD::addressof(__p->__value_));
            __node_traits::deallocate(__a, __p, 1);
        }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
#ifndef _LIBCPP_HAS_NO_VARIADICS

        template<class _Tp, class _Alloc>
        template<class... _Args>
        typename forward_list<_Tp, _Alloc>::iterator
        forward_list<_Tp, _Alloc>::emplace_after(const_iterator __p, _Args&& ... __args) {
            __node_pointer const __r = __p.__ptr_;
            __node_allocator& __a = base::__alloc();
            typedef __allocator_destructor<__node_allocator> _Dp;
            unique_ptr<__node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
            __node_traits::construct(__a, _VSTD::addressof(__h->__value_),
                                     _VSTD::forward<_Args>(__args)...);
            __h->__next_ = __r->__next_;
            __r->__next_ = __h.release();
            return iterator(__r->__next_);
        }

#endif  // _LIBCPP_HAS_NO_VARIADICS

        template<class _Tp, class _Alloc>
        typename forward_list<_Tp, _Alloc>::iterator
        forward_list<_Tp, _Alloc>::insert_after(const_iterator __p, value_type&& __v) {
            __node_pointer const __r = __p.__ptr_;
            __node_allocator& __a = base::__alloc();
            typedef __allocator_destructor<__node_allocator> _Dp;
            unique_ptr<__node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
            __node_traits::construct(__a, _VSTD::addressof(__h->__value_), _VSTD::move(__v));
            __h->__next_ = __r->__next_;
            __r->__next_ = __h.release();
            return iterator(__r->__next_);
        }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

        template<class _Tp, class _Alloc>
        typename forward_list<_Tp, _Alloc>::iterator
        forward_list<_Tp, _Alloc>::insert_after(const_iterator __p, const value_type& __v) {
            __node_pointer const __r = __p.__ptr_;
            __node_allocator& __a = base::__alloc();
            typedef __allocator_destructor<__node_allocator> _Dp;
            unique_ptr<__node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
            __node_traits::construct(__a, _VSTD::addressof(__h->__value_), __v);
            __h->__next_ = __r->__next_;
            __r->__next_ = __h.release();
            return iterator(__r->__next_);
        }

        template<class _Tp, class _Alloc>
        typename forward_list<_Tp, _Alloc>::iterator
        forward_list<_Tp, _Alloc>::insert_after(const_iterator __p, size_type __n,
                                                const value_type& __v) {
            __node_pointer __r = __p.__ptr_;
            if (__n > 0) {
                __node_allocator& __a = base::__alloc();
                typedef __allocator_destructor<__node_allocator> _Dp;
                unique_ptr<__node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
                __node_traits::construct(__a, _VSTD::addressof(__h->__value_), __v);
                __node_pointer __first = __h.release();
                __node_pointer __last = __first;
#ifndef _LIBCPP_NO_EXCEPTIONS
                try {
#endif  // _LIBCPP_NO_EXCEPTIONS
                    for (--__n; __n != 0; --__n, __last = __last->__next_) {
                        __h.reset(__node_traits::allocate(__a, 1));
                        __node_traits::construct(__a, _VSTD::addressof(__h->__value_), __v);
                        __last->__next_ = __h.release();
                    }
#ifndef _LIBCPP_NO_EXCEPTIONS
                }
                catch (...) {
                    while (__first != nullptr) {
                        __node_pointer __next = __first->__next_;
                        __node_traits::destroy(__a, _VSTD::addressof(__first->__value_));
                        __node_traits::deallocate(__a, __first, 1);
                        __first = __next;
                    }
                    throw;
                }
#endif  // _LIBCPP_NO_EXCEPTIONS
                __last->__next_ = __r->__next_;
                __r->__next_ = __first;
                __r = __last;
            }
            return iterator(__r);
        }

        template<class _Tp, class _Alloc>
        template<class _InputIterator>
        typename enable_if
                <
                        __is_input_iterator<_InputIterator>::value,
                        typename forward_list<_Tp, _Alloc>::iterator
                >::type
        forward_list<_Tp, _Alloc>::insert_after(const_iterator __p,
                                                _InputIterator __f, _InputIterator __l) {
            __node_pointer __r = __p.__ptr_;
            if (__f != __l) {
                __node_allocator& __a = base::__alloc();
                typedef __allocator_destructor<__node_allocator> _Dp;
                unique_ptr<__node, _Dp> __h(__node_traits::allocate(__a, 1), _Dp(__a, 1));
                __node_traits::construct(__a, _VSTD::addressof(__h->__value_), *__f);
                __node_pointer __first = __h.release();
                __node_pointer __last = __first;
#ifndef _LIBCPP_NO_EXCEPTIONS
                try {
#endif  // _LIBCPP_NO_EXCEPTIONS
                    for (++__f; __f != __l; ++__f, ((void) (__last = __last->__next_))) {
                        __h.reset(__node_traits::allocate(__a, 1));
                        __node_traits::construct(__a, _VSTD::addressof(__h->__value_), *__f);
                        __last->__next_ = __h.release();
                    }
#ifndef _LIBCPP_NO_EXCEPTIONS
                }
                catch (...) {
                    while (__first != nullptr) {
                        __node_pointer __next = __first->__next_;
                        __node_traits::destroy(__a, _VSTD::addressof(__first->__value_));
                        __node_traits::deallocate(__a, __first, 1);
                        __first = __next;
                    }
                    throw;
                }
#endif  // _LIBCPP_NO_EXCEPTIONS
                __last->__next_ = __r->__next_;
                __r->__next_ = __first;
                __r = __last;
            }
            return iterator(__r);
        }

        template<class _Tp, class _Alloc>
        typename forward_list<_Tp, _Alloc>::iterator
        forward_list<_Tp, _Alloc>::erase_after(const_iterator __f) {
            __node_pointer __p = __f.__ptr_;
            __node_pointer __n = __p->__next_;
            __p->__next_ = __n->__next_;
            __node_allocator& __a = base::__alloc();
            __node_traits::destroy(__a, _VSTD::addressof(__n->__value_));
            __node_traits::deallocate(__a, __n, 1);
            return iterator(__p->__next_);
        }

        template<class _Tp, class _Alloc>
        typename forward_list<_Tp, _Alloc>::iterator
        forward_list<_Tp, _Alloc>::erase_after(const_iterator __f, const_iterator __l) {
            __node_pointer __e = __l.__ptr_;
            if (__f != __l) {
                __node_pointer __p = __f.__ptr_;
                __node_pointer __n = __p->__next_;
                if (__n != __e) {
                    __p->__next_ = __e;
                    __node_allocator& __a = base::__alloc();
                    do {
                        __p = __n->__next_;
                        __node_traits::destroy(__a, _VSTD::addressof(__n->__value_));
                        __node_traits::deallocate(__a, __n, 1);
                        __n = __p;
                    } while (__n != __e);
                }
            }
            return iterator(__e);
        }

        template<class _Tp, class _Alloc>
        void
        forward_list<_Tp, _Alloc>::resize(size_type __n) {
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
                    __node_allocator& __a = base::__alloc();
                    typedef __allocator_destructor<__node_allocator> _Dp;
                    unique_ptr<__node, _Dp> __h(nullptr, _Dp(__a, 1));
                    for (__node_pointer __ptr = __p.__ptr_; __n > 0; --__n,
                            __ptr = __ptr->__next_) {
                        __h.reset(__node_traits::allocate(__a, 1));
                        __node_traits::construct(__a, _VSTD::addressof(__h->__value_));
                        __h->__next_ = nullptr;
                        __ptr->__next_ = __h.release();
                    }
                }
            }
        }

        template<class _Tp, class _Alloc>
        void
        forward_list<_Tp, _Alloc>::resize(size_type __n, const value_type& __v) {
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
                    __node_allocator& __a = base::__alloc();
                    typedef __allocator_destructor<__node_allocator> _Dp;
                    unique_ptr<__node, _Dp> __h(nullptr, _Dp(__a, 1));
                    for (__node_pointer __ptr = __p.__ptr_; __n > 0; --__n,
                            __ptr = __ptr->__next_) {
                        __h.reset(__node_traits::allocate(__a, 1));
                        __node_traits::construct(__a, _VSTD::addressof(__h->__value_), __v);
                        __h->__next_ = nullptr;
                        __ptr->__next_ = __h.release();
                    }
                }
            }
        }

        template<class _Tp, class _Alloc>
        void
        forward_list<_Tp, _Alloc>::splice_after(const_iterator __p,
                                                forward_list& __x) {
            if (!__x.empty()) {
                if (__p.__ptr_->__next_ != nullptr) {
                    const_iterator __lm1 = __x.before_begin();
                    while (__lm1.__ptr_->__next_ != nullptr)
                        ++__lm1;
                    __lm1.__ptr_->__next_ = __p.__ptr_->__next_;
                }
                __p.__ptr_->__next_ = __x.__before_begin()->__next_;
                __x.__before_begin()->__next_ = nullptr;
            }
        }

        template<class _Tp, class _Alloc>
        void
        forward_list<_Tp, _Alloc>::splice_after(const_iterator __p,
                                                forward_list& __x,
                                                const_iterator __i) {
            const_iterator __lm1 = _VSTD::next(__i);
            if (__p != __i && __p != __lm1) {
                __i.__ptr_->__next_ = __lm1.__ptr_->__next_;
                __lm1.__ptr_->__next_ = __p.__ptr_->__next_;
                __p.__ptr_->__next_ = __lm1.__ptr_;
            }
        }

        template<class _Tp, class _Alloc>
        void
        forward_list<_Tp, _Alloc>::splice_after(const_iterator __p,
                                                forward_list& __x,
                                                const_iterator __f, const_iterator __l) {
            if (__f != __l && __p != __f) {
                const_iterator __lm1 = __f;
                while (__lm1.__ptr_->__next_ != __l.__ptr_)
                    ++__lm1;
                if (__f != __lm1) {
                    __lm1.__ptr_->__next_ = __p.__ptr_->__next_;
                    __p.__ptr_->__next_ = __f.__ptr_->__next_;
                    __f.__ptr_->__next_ = __l.__ptr_;
                }
            }
        }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

        template<class _Tp, class _Alloc>
        inline _LIBCPP_INLINE_VISIBILITY
        void
        forward_list<_Tp, _Alloc>::splice_after(const_iterator __p,
                                                forward_list&& __x) {
            splice_after(__p, __x);
        }

        template<class _Tp, class _Alloc>
        inline _LIBCPP_INLINE_VISIBILITY
        void
        forward_list<_Tp, _Alloc>::splice_after(const_iterator __p,
                                                forward_list&& __x,
                                                const_iterator __i) {
            splice_after(__p, __x, __i);
        }

        template<class _Tp, class _Alloc>
        inline _LIBCPP_INLINE_VISIBILITY
        void
        forward_list<_Tp, _Alloc>::splice_after(const_iterator __p,
                                                forward_list&& __x,
                                                const_iterator __f, const_iterator __l) {
            splice_after(__p, __x, __f, __l);
        }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

        template<class _Tp, class _Alloc>
        void
        forward_list<_Tp, _Alloc>::remove(const value_type& __v) {
            forward_list<_Tp, _Alloc> __deleted_nodes; // collect the nodes we're removing
            iterator __e = end();
            for (iterator __i = before_begin(); __i.__ptr_->__next_ != nullptr;) {
                if (__i.__ptr_->__next_->__value_ == __v) {
                    iterator __j = _VSTD::next(__i, 2);
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

        template<class _Tp, class _Alloc>
        template<class _Predicate>
        void
        forward_list<_Tp, _Alloc>::remove_if(_Predicate __pred) {
            iterator __e = end();
            for (iterator __i = before_begin(); __i.__ptr_->__next_ != nullptr;) {
                if (__pred(__i.__ptr_->__next_->__value_)) {
                    iterator __j = _VSTD::next(__i, 2);
                    for (; __j != __e && __pred(*__j); ++__j);
                    erase_after(__i, __j);
                    if (__j == __e)
                        break;
                    __i = __j;
                }
                else
                    ++__i;
            }
        }

        template<class _Tp, class _Alloc>
        template<class _BinaryPredicate>
        void
        forward_list<_Tp, _Alloc>::unique(_BinaryPredicate __binary_pred) {
            for (iterator __i = begin(), __e = end(); __i != __e;) {
                iterator __j = _VSTD::next(__i);
                for (; __j != __e && __binary_pred(*__i, *__j); ++__j);
                if (__i.__ptr_->__next_ != __j.__ptr_)
                    erase_after(__i, __j);
                __i = __j;
            }
        }

        template<class _Tp, class _Alloc>
        template<class _Compare>
        void
        forward_list<_Tp, _Alloc>::merge(forward_list& __x, _Compare __comp) {
            if (this != &__x) {
                base::__before_begin()->__next_ = __merge(base::__before_begin()->__next_,
                                                          __x.__before_begin()->__next_,
                                                          __comp);
                __x.__before_begin()->__next_ = nullptr;
            }
        }

        template<class _Tp, class _Alloc>
        template<class _Compare>
        typename forward_list<_Tp, _Alloc>::__node_pointer
        forward_list<_Tp, _Alloc>::__merge(__node_pointer __f1, __node_pointer __f2,
                                           _Compare& __comp) {
            if (__f1 == nullptr)
                return __f2;
            if (__f2 == nullptr)
                return __f1;
            __node_pointer __r;
            if (__comp(__f2->__value_, __f1->__value_)) {
                __node_pointer __t = __f2;
                while (__t->__next_ != nullptr &&
                       __comp(__t->__next_->__value_, __f1->__value_))
                    __t = __t->__next_;
                __r = __f2;
                __f2 = __t->__next_;
                __t->__next_ = __f1;
            }
            else
                __r = __f1;
            __node_pointer __p = __f1;
            __f1 = __f1->__next_;
            while (__f1 != nullptr && __f2 != nullptr) {
                if (__comp(__f2->__value_, __f1->__value_)) {
                    __node_pointer __t = __f2;
                    while (__t->__next_ != nullptr &&
                           __comp(__t->__next_->__value_, __f1->__value_))
                        __t = __t->__next_;
                    __p->__next_ = __f2;
                    __f2 = __t->__next_;
                    __t->__next_ = __f1;
                }
                __p = __f1;
                __f1 = __f1->__next_;
            }
            if (__f2 != nullptr)
                __p->__next_ = __f2;
            return __r;
        }

        template<class _Tp, class _Alloc>
        template<class _Compare>
        inline _LIBCPP_INLINE_VISIBILITY
        void
        forward_list<_Tp, _Alloc>::sort(_Compare __comp) {
            base::__before_begin()->__next_ = __sort(base::__before_begin()->__next_,
                                                     _VSTD::distance(begin(), end()), __comp);
        }

        template<class _Tp, class _Alloc>
        template<class _Compare>
        typename forward_list<_Tp, _Alloc>::__node_pointer
        forward_list<_Tp, _Alloc>::__sort(__node_pointer __f1, difference_type __sz,
                                          _Compare& __comp) {
            switch (__sz) {
                case 0:
                case 1:
                    return __f1;
                case 2:
                    if (__comp(__f1->__next_->__value_, __f1->__value_)) {
                        __node_pointer __t = __f1->__next_;
                        __t->__next_ = __f1;
                        __f1->__next_ = nullptr;
                        __f1 = __t;
                    }
                    return __f1;
            }
            difference_type __sz1 = __sz / 2;
            difference_type __sz2 = __sz - __sz1;
            __node_pointer __t = _VSTD::next(iterator(__f1), __sz1 - 1).__ptr_;
            __node_pointer __f2 = __t->__next_;
            __t->__next_ = nullptr;
            return __merge(__sort(__f1, __sz1, __comp),
                           __sort(__f2, __sz2, __comp), __comp);
        }

        template<class _Tp, class _Alloc>
        void
        forward_list<_Tp, _Alloc>::reverse() _NOEXCEPT {
            __node_pointer __p = base::__before_begin()->__next_;
            if (__p != nullptr) {
                __node_pointer __f = __p->__next_;
                __p->__next_ = nullptr;
                while (__f != nullptr) {
                    __node_pointer __t = __f->__next_;
                    __f->__next_ = __p;
                    __p = __f;
                    __f = __t;
                }
                base::__before_begin()->__next_ = __p;
            }
        }

        template<class _Tp, class _Alloc>
        bool operator==(const forward_list<_Tp, _Alloc>& __x,
                        const forward_list<_Tp, _Alloc>& __y) {
            typedef forward_list<_Tp, _Alloc> _Cp;
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

        template<class _Tp, class _Alloc>
        inline _LIBCPP_INLINE_VISIBILITY
        bool operator!=(const forward_list<_Tp, _Alloc>& __x,
                        const forward_list<_Tp, _Alloc>& __y) {
            return !(__x == __y);
        }

        template<class _Tp, class _Alloc>
        inline _LIBCPP_INLINE_VISIBILITY
        bool operator<(const forward_list<_Tp, _Alloc>& __x,
                       const forward_list<_Tp, _Alloc>& __y) {
            return _VSTD::lexicographical_compare(__x.begin(), __x.end(),
                                                  __y.begin(), __y.end());
        }

        template<class _Tp, class _Alloc>
        inline _LIBCPP_INLINE_VISIBILITY
        bool operator>(const forward_list<_Tp, _Alloc>& __x,
                       const forward_list<_Tp, _Alloc>& __y) {
            return __y < __x;
        }

        template<class _Tp, class _Alloc>
        inline _LIBCPP_INLINE_VISIBILITY
        bool operator>=(const forward_list<_Tp, _Alloc>& __x,
                        const forward_list<_Tp, _Alloc>& __y) {
            return !(__x < __y);
        }

        template<class _Tp, class _Alloc>
        inline _LIBCPP_INLINE_VISIBILITY
        bool operator<=(const forward_list<_Tp, _Alloc>& __x,
                        const forward_list<_Tp, _Alloc>& __y) {
            return !(__y < __x);
        }

        template<class _Tp, class _Alloc>
        inline _LIBCPP_INLINE_VISIBILITY
        void
        swap(forward_list<_Tp, _Alloc>& __x, forward_list<_Tp, _Alloc>& __y)
        _NOEXCEPT_(_NOEXCEPT_(__x.swap(__y))) {
            __x.swap(__y);
        }

_LIBCPP_END_NAMESPACE_STD

#endif  // _LIBCPP_FORWARD_LIST
