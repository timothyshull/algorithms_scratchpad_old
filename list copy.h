#ifndef CPP_DATA_STRUCTURES_LIST_H
#define CPP_DATA_STRUCTURES_LIST_H

#include <memory>
#include <limits>
#include <initializer_list>
#include <iterator>
#include <algorithm>
#include "mem_util.h"

using std::pointer_traits;
using std::allocator;
using std::bidirectional_iterator_tag;
using std::allocator_traits;
using std::integral_constant;
using compressed_pair = std::__compressed_pair;
using std::integral_constant;
using std::true_type;
using std::false_type;
using std::initializer_list;
using is_input_iterator = std::__is_input_iterator;
using std::numeric_limits;
using std::unique_ptr;
using std::enable_if;

namespace algos2 {

    template<class Tp, class VoidPtr>
    struct list_node;

    template<class Tp, class VoidPtr>
    struct list_node_base {
        using pointer = typename rebind_pointer<VoidPtr, list_node<Tp, VoidPtr> >::type;
        using base_pointer =  typename rebind_pointer<VoidPtr, list_node_base>::type;

        pointer _prev;
        pointer _next;

        list_node_base() : _prev(_self()), _next(_self()) { }

        pointer _self() {
            return static_cast<pointer>(pointer_traits<base_pointer>::pointer_to(*this));
        }
    };

    template<class Tp, class VoidPtr>
    struct list_node : public list_node_base<Tp, VoidPtr> {
        Tp _value;
    };

    template<class Tp, class Alloc = allocator<Tp> >
    class list;

    template<class Tp, class Alloc>
    class list_imp;

    template<class Tp, class VoidPtr>
    class list_const_iterator;

    template<class Tp, class VoidPtr>
    class list_iterator {
        using node_pointer = typename rebind_pointer<VoidPtr, list_node<Tp, VoidPtr> >::type;

        node_pointer _ptr;

        explicit list_iterator(node_pointer __p) noexcept : _ptr(__p) { }

        template<class, class> friend
        class list;

        template<class, class> friend
        class list_imp;

        template<class, class> friend
        class list_const_iterator;

    public:
        using iterator_category = bidirectional_iterator_tag;
        using value_type = Tp;
        using reference = value_type&;
        using pointer = typename rebind_pointer<VoidPtr, value_type>::type;
        using difference_type = typename pointer_traits<pointer>::difference_type;

        list_iterator() noexcept : _ptr(nullptr) { }

        reference operator*() const {
            return _ptr->_value;
        }

        pointer operator->() const {
            return pointer_traits<pointer>::pointer_to(_ptr->_value);
        }

        list_iterator& operator++() {
            _ptr = _ptr->_next;
            return *this;
        }

        list_iterator operator++(int) {
            list_iterator __t(*this);
            ++(*this);
            return __t;
        }

        list_iterator& operator--() {
            _ptr = _ptr->_prev;
            return *this;
        }

        list_iterator operator--(int) {
            list_iterator __t(*this);
            --(*this);
            return __t;
        }

        friend
        bool operator==(const list_iterator& __x, const list_iterator& __y) {
            return __x._ptr == __y._ptr;
        }

        friend
        bool operator!=(const list_iterator& __x, const list_iterator& __y) { return !(__x == __y); }
    };

    template<class Tp, class VoidPtr>
    class list_const_iterator {
        using node_pointer = typename rebind_pointer<VoidPtr, list_node<Tp, VoidPtr> >::type;

        node_pointer _ptr;

        explicit list_const_iterator(node_pointer __p) noexcept : _ptr(__p) { }

        template<class, class> friend
        class list;

        template<class, class> friend
        class list_imp;

    public:
        using iterator_category = bidirectional_iterator_tag;
        using value_type = Tp;
        using reference = const value_type&;
        using pointer = typename rebind_pointer<VoidPtr, const value_type>::type;
        using difference_type = typename pointer_traits<pointer>::difference_type;

        list_const_iterator() noexcept : _ptr(nullptr) { }

        list_const_iterator(const list_iterator<Tp, VoidPtr>& __p) noexcept : _ptr(__p._ptr) { }

        reference operator*() const {
            return _ptr->_value;
        }

        pointer operator->() const {
            return pointer_traits<pointer>::pointer_to(_ptr->_value);
        }

        list_const_iterator& operator++() {
            _ptr = _ptr->_next;
            return *this;
        }

        list_const_iterator operator++(int) {
            list_const_iterator __t(*this);
            ++(*this);
            return __t;
        }

        list_const_iterator& operator--() {
            _ptr = _ptr->_prev;
            return *this;
        }

        list_const_iterator operator--(int) {
            list_const_iterator __t(*this);
            --(*this);
            return __t;
        }

        friend
        bool operator==(const list_const_iterator& __x, const list_const_iterator& __y) {
            return __x._ptr == __y._ptr;
        }

        friend
        bool operator!=(const list_const_iterator& __x, const list_const_iterator& __y) { return !(__x == __y); }
    };

    template<class Tp, class Alloc>
    class list_imp {
        list_imp(const list_imp&);

        list_imp& operator=(const list_imp&);

    protected:
        using value_type = Tp;
        using allocator_type = Alloc;
        using alloc_traits = allocator_traits<allocator_type>;
        using size_type = typename alloc_traits::size_type;
        using _void_pointer = typename alloc_traits::void_pointer;
        using iterator = list_iterator<value_type, _void_pointer>;
        using const_iterator = list_const_iterator<value_type, _void_pointer>;
        using node_base = list_node_base<value_type, _void_pointer>;
        using node = list_node<value_type, _void_pointer>;
        using node_allocator = typename rebind_alloc_helper<alloc_traits, node>::type;
        using node_alloc_traits = allocator_traits<node_allocator>;
        using node_pointer = typename node_alloc_traits::pointer;
        using node_const_pointer = typename node_alloc_traits::pointer;
        using pointer = typename alloc_traits::pointer;
        using const_pointer = typename alloc_traits::const_pointer;
        using difference_type = typename alloc_traits::difference_type;

        using node_base_allocator = typename rebind_alloc_helper<alloc_traits, node_base>::type;
        using node_base_pointer = typename allocator_traits<node_base_allocator>::pointer;

        node_base _end;
        compressed_pair<size_type, node_allocator> _size_alloc;

        size_type& __sz() noexcept { return _size_alloc.first(); }

        const size_type& __sz() const noexcept { return _size_alloc.first(); }

        node_allocator& __node_alloc() noexcept { return _size_alloc.second(); }

        const node_allocator& __node_alloc() const noexcept { return _size_alloc.second(); }

        static void __unlink_nodes(node_pointer __f, node_pointer __l) noexcept;

        list_imp() noexcept(std::is_nothrow_default_constructible<node_allocator>::value);

        list_imp(const allocator_type& __a);

        ~list_imp();

        virtual void clear() noexcept;

        virtual bool empty() const noexcept { return __sz() == 0; }

        virtual iterator begin() noexcept {
            return iterator(_end._next);
        }

        virtual const_iterator begin() const noexcept {
            return const_iterator(_end._next);
        }

        virtual iterator end() noexcept {
//            return iterator(static_cast<node_pointer>(pointer_traits<node_base_pointer>::pointer_to(_end)));
            return iterator(static_cast<node_pointer>(std::addressof(_end)));
        }

        virtual const_iterator end() const noexcept {
//            return const_iterator(static_cast<node_const_pointer>(pointer_traits<node_base_pointer>::pointer_to(const_cast<node_base&>(_end))));
            return const_iterator(static_cast<node_const_pointer>(std::addressof(const_cast<node_base&>(_end))));
        }

        void swap(list_imp& __c) noexcept;

        void _copy_assign_alloc(const list_imp& __c) {
            _copy_assign_alloc(__c, integral_constant<bool, node_alloc_traits::propagate_on_container_copy_assignment::value>());
        }

        void _move_assign_alloc(list_imp& __c) noexcept {
            _move_assign_alloc(__c, integral_constant<bool, node_alloc_traits::propagate_on_container_move_assignment::value>());
        }

    private:
        void _copy_assign_alloc(const list_imp& __c, true_type) {
            if (__node_alloc() != __c.__node_alloc())
                clear();
            __node_alloc() = __c.__node_alloc();
        }


        void _copy_assign_alloc(const list_imp& __c, false_type) { }


        void _move_assign_alloc(list_imp& __c,
                                true_type) noexcept(std::is_nothrow_move_assignable<node_allocator>::value) {
            __node_alloc() = std::move(__c.__node_alloc());
        }


        void _move_assign_alloc(list_imp& __c, false_type)
        noexcept { }
    };

// Unlink nodes [__f, __l]
    template<class Tp, class Alloc>
    inline
    void
    list_imp<Tp, Alloc>::__unlink_nodes(node_pointer __f, node_pointer __l)
    noexcept {
        __f->_prev->_next = __l->_next;
        __l->_next->_prev = __f->_prev;
    }

    template<class Tp, class Alloc>
    inline
    list_imp<Tp, Alloc>::list_imp() noexcept(std::is_nothrow_default_constructible<node_allocator>::value) :
            _size_alloc(0) {
    }

    template<class Tp, class Alloc>
    inline
    list_imp<Tp, Alloc>::list_imp(const allocator_type& __a)
            : _size_alloc(0, node_allocator(__a)) {
    }

    template<class Tp, class Alloc>
    list_imp<Tp, Alloc>::~list_imp() {
        clear();
    }

    template<class Tp, class Alloc>
    void
    list_imp<Tp, Alloc>::clear() noexcept {
        if (!empty()) {
            node_allocator& __na = __node_alloc();
            node_pointer __f = _end._next;
//            node_pointer __l = static_cast<node_pointer>(pointer_traits<node_base_pointer>::pointer_to(_end));
            node_pointer __l = static_cast<node_pointer>(std::addressof(_end));
            __unlink_nodes(__f, __l->_prev);
            __sz() = 0;
            while (__f != __l) {
                node_pointer __n = __f;
                __f = __f->_next;
                node_alloc_traits::destroy(__na, std::addressof(__n->_value));
                node_alloc_traits::deallocate(__na, __n, 1);
            }
        }
    }

    template<class Tp, class Alloc>
    void
    list_imp<Tp, Alloc>::swap(list_imp& __c)
    noexcept {
        using std::swap;
        std::swap(__node_alloc(), __c.__node_alloc());
        swap(__sz(), __c.__sz());
        swap(_end, __c._end);
        if (__sz() == 0)
            _end._next = _end._prev = _end._self();
        else
            _end._prev->_next = _end._next->_prev = _end._self();
        if (__c.__sz() == 0)
            __c._end._next = __c._end._prev = __c._end._self();
        else
            __c._end._prev->_next = __c._end._next->_prev = __c._end._self();

    }

    template<class Tp, class Alloc /*= allocator<Tp>*/>
    class list : private list_imp<Tp, Alloc> {
        using base = list_imp<Tp, Alloc>;
        using _node =  typename base::node;
        using _node_allocator =  typename base::node_allocator;
        using _node_pointer =  typename base::node_pointer;
        using _node_alloc_traits =  typename base::node_alloc_traits;
        using _node_base =  typename base::node_base;
        using _node_base_pointer =  typename base::node_base_pointer;

    public:
        using value_type =  Tp;
        using allocator_type =  Alloc;
        using reference =  value_type&;
        using const_reference =  const value_type&;
        using pointer =  typename base::pointer;
        using const_pointer =  typename base::const_pointer;
        using size_type =  typename base::size_type;
        using difference_type =  typename base::difference_type;
        using iterator =  typename base::iterator;
        using const_iterator =  typename base::const_iterator;
        using reverse_iterator =  std::reverse_iterator<iterator>;
        using const_reverse_iterator =  std::reverse_iterator<const_iterator>;


        list() noexcept(std::is_nothrow_default_constructible<_node_allocator>::value) { }

        explicit list(const allocator_type& __a) : base(__a) { }

        explicit list(size_type __n);

        explicit list(size_type __n, const allocator_type& __a);

//        list(size_type __n, const value_type& __x);

        list(size_type __n, const value_type& __x, const allocator_type& __a);

        template<class _InpIter>
        list(_InpIter __f, _InpIter __l,
             typename enable_if<is_input_iterator<_InpIter>::value>::type* = 0);

        template<class _InpIter>
        list(_InpIter __f, _InpIter __l, const allocator_type& __a,
             typename enable_if<is_input_iterator<_InpIter>::value>::type* = 0);

        list(const list& __c);

        list(const list& __c, const allocator_type& __a);

        list& operator=(const list& __c);

        list(initializer_list<value_type> __il);

        list(initializer_list<value_type> __il, const allocator_type& __a);

        list(list&& __c) noexcept(std::is_nothrow_move_constructible<_node_allocator>::value);

        list(list&& __c, const allocator_type& __a);

        list& operator=(list&& __c) noexcept(_node_alloc_traits::propagate_on_container_move_assignment::value && std::is_nothrow_move_assignable<_node_allocator>::value);

        list& operator=(initializer_list<value_type> __il) {
            assign(__il.begin(), __il.end());
            return *this;
        }

        template<class _InpIter>
        void assign(_InpIter __f, _InpIter __l,
                    typename enable_if<is_input_iterator<_InpIter>::value>::type* = 0);

        void assign(size_type __n, const value_type& __x);

        void assign(initializer_list<value_type> __il) { assign(__il.begin(), __il.end()); }

        allocator_type getAllocator() const noexcept;

        size_type size() const noexcept { return base::__sz(); }

        bool empty() const noexcept { return base::empty(); }

        size_type max_size() const noexcept { return static_cast<size_type>(numeric_limits<difference_type>::max()); }

        iterator begin() noexcept { return base::begin(); }

        const_iterator begin() const noexcept { return base::begin(); }

        iterator end() noexcept { return base::end(); }

        const_iterator end() const noexcept { return base::end(); }

        const_iterator cbegin() const noexcept { return base::begin(); }

        const_iterator cend() const noexcept { return base::end(); }

        reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

        reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

        const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

        const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

        reference front() {
            return base::_end._next->_value;
        }

        const_reference front() const {
            return base::_end._next->_value;
        }

        reference back() {
            return base::_end._prev->_value;
        }

        const_reference back() const {
            return base::_end._prev->_value;
        }

        void push_front(value_type&& __x);

        void push_back(value_type&& __x);

        template<class... _Args>
        void emplace_front(_Args&& ... __args);

        template<class... _Args>
        void emplace_back(_Args&& ... __args);

        template<class... _Args>
        iterator emplace(const_iterator __p, _Args&& ... __args);

        iterator insert(const_iterator __p, value_type&& __x);

        void push_front(const value_type& __x);

        void push_back(const value_type& __x);

        iterator insert(const_iterator __p, const value_type& __x);

        iterator insert(const_iterator __p, size_type __n, const value_type& __x);

        template<class _InpIter>
        iterator insert(const_iterator __p, _InpIter __f, _InpIter __l,
                        typename enable_if<is_input_iterator<_InpIter>::value>::type* = 0);

        iterator insert(const_iterator __p, initializer_list<value_type> __il) {
            return insert(__p, __il.begin(), __il.end());
        }

        void swap(list& __c) noexcept { base::swap(__c); }

        void clear() noexcept { base::clear(); }

        void pop_front();

        void pop_back();

        iterator erase(const_iterator __p);

        iterator erase(const_iterator __f, const_iterator __l);

        void resize(size_type __n);

        void resize(size_type __n, const value_type& __x);

        void splice(const_iterator __p, list& __c);

        void splice(const_iterator __p, list&& __c) { splice(__p, __c); }

        void splice(const_iterator __p, list& __c, const_iterator __i);

        void splice(const_iterator __p, list&& __c, const_iterator __i) { splice(__p, __c, __i); }

        void splice(const_iterator __p, list& __c, const_iterator __f, const_iterator __l);

        void splice(const_iterator __p, list&& __c, const_iterator __f, const_iterator __l) {
            splice(__p, __c, __f, __l);
        }

        void remove(const value_type& __x);

        template<class _Pred>
        void remove_if(_Pred __pred);

        void unique();

        template<class _BinaryPred>
        void unique(_BinaryPred __binary_pred);

        void merge(list& __c);

        void merge(list&& __c) { merge(__c); }

        template<class _Comp>
        void merge(list& __c, _Comp __comp);

        template<class _Comp>

        void merge(list&& __c, _Comp __comp) { merge(__c, __comp); }

        void sort();

        template<class _Comp>
        void sort(_Comp __comp);

        void reverse() noexcept;

        bool __invariants() const;

    private:
        static void __link_nodes(_node_pointer __p, _node_pointer __f, _node_pointer __l);

        void __link_nodes_at_front(_node_pointer __f, _node_pointer __l);

        void __link_nodes_at_back(_node_pointer __f, _node_pointer __l);

        iterator __iterator(size_type __n);

        template<class _Comp>
        static iterator __sort(iterator __f1, iterator __e2, size_type __n, _Comp& __comp);

        void __move_assign(list& __c, true_type) noexcept(std::is_nothrow_move_assignable<_node_allocator>::value);

        void __move_assign(list& __c, false_type);
    };

    template<class Tp, class Alloc>
    inline
    void
    list<Tp, Alloc>::__link_nodes(_node_pointer __p, _node_pointer __f, _node_pointer __l) {
        __p->_prev->_next = __f;
        __f->_prev = __p->_prev;
        __p->_prev = __l;
        __l->_next = __p;
    }

    template<class Tp, class Alloc>
    inline
    void
    list<Tp, Alloc>::__link_nodes_at_front(_node_pointer __f, _node_pointer __l) {
        __f->_prev = base::_end._self();
        __l->_next = base::_end._next;
        __l->_next->_prev = __l;
        base::_end._next = __f;
    }

    template<class Tp, class Alloc>
    inline
    void
    list<Tp, Alloc>::__link_nodes_at_back(_node_pointer __f, _node_pointer __l) {
        __l->_next = base::_end._self();
        __f->_prev = base::_end._prev;
        __f->_prev->_next = __f;
        base::_end._prev = __l;
    }

    template<class Tp, class Alloc>
    inline
    typename list<Tp, Alloc>::iterator
    list<Tp, Alloc>::__iterator(size_type __n) {
        return __n <= base::__sz() / 2 ? std::next(begin(), __n)
                                       : std::prev(end(), base::__sz() - __n);
    }

    template<class Tp, class Alloc>
    list<Tp, Alloc>::list(size_type __n) {
        for (; __n > 0; --__n)
            emplace_back();
    }

    template<class Tp, class Alloc>
    list<Tp, Alloc>::list(size_type __n, const allocator_type& __a) : base(__a) {
        for (; __n > 0; --__n)
            emplace_back();
    }

    template<class Tp, class Alloc>
    list<Tp, Alloc>::list(size_type __n, const value_type& __x) {
        for (; __n > 0; --__n)
            push_back(__x);
    }

    template<class Tp, class Alloc>
    list<Tp, Alloc>::list(size_type __n, const value_type& __x, const allocator_type& __a)
            : base(__a) {
        for (; __n > 0; --__n)
            push_back(__x);
    }

    template<class Tp, class Alloc>
    template<class _InpIter>
    list<Tp, Alloc>::list(_InpIter __f, _InpIter __l,
                          typename enable_if<is_input_iterator<_InpIter>::value>::type*) {
        for (; __f != __l; ++__f)
            push_back(*__f);
    }

    template<class Tp, class Alloc>
    template<class _InpIter>
    list<Tp, Alloc>::list(_InpIter __f, _InpIter __l, const allocator_type& __a,
                          typename enable_if<is_input_iterator<_InpIter>::value>::type*)
            : base(__a) {
        for (; __f != __l; ++__f)
            push_back(*__f);
    }

    template<class Tp, class Alloc>
    list<Tp, Alloc>::list(const list& __c)
            : base(allocator_type(
            _node_alloc_traits::select_on_container_copy_construction(
                    __c.__node_alloc()))) {
        for (const_iterator __i = __c.begin(), __e = __c.end(); __i != __e; ++__i)
            push_back(*__i);
    }

    template<class Tp, class Alloc>
    list<Tp, Alloc>::list(const list& __c, const allocator_type& __a)
            : base(__a) {
        for (const_iterator __i = __c.begin(), __e = __c.end(); __i != __e; ++__i)
            push_back(*__i);
    }

    template<class Tp, class Alloc>
    list<Tp, Alloc>::list(initializer_list<value_type> __il, const allocator_type& __a)
            : base(__a) {
        for (typename initializer_list<value_type>::const_iterator __i = __il.begin(),
                     __e = __il.end(); __i != __e; ++__i)
            push_back(*__i);
    }

    template<class Tp, class Alloc>
    list<Tp, Alloc>::list(initializer_list<value_type> __il) {
        for (typename initializer_list<value_type>::const_iterator __i = __il.begin(),
                     __e = __il.end(); __i != __e; ++__i)
            push_back(*__i);
    }

    template<class Tp, class Alloc>
    inline
    list<Tp, Alloc>&
    list<Tp, Alloc>::operator=(const list& __c) {
        if (this != &__c) {
            base::_copy_assign_alloc(__c);
            assign(__c.begin(), __c.end());
        }
        return *this;
    }

    template<class Tp, class Alloc>
    inline
    list<Tp, Alloc>::list(list&& __c)

    noexcept(std::is_nothrow_move_constructible<_node_allocator>::value)
            :
            base(allocator_type(std::move(__c.__node_alloc()))) {
        splice(end(), __c);
    }

    template<class Tp, class Alloc>
    inline
    list<Tp, Alloc>::list(list&& __c, const allocator_type& __a)
            : base(__a) {
        if (__a == __c.getAllocator())
            splice(end(), __c);
        else {
            using _Ip = std::move_iterator<iterator>;
            assign(_Ip(__c.begin()), _Ip(__c.end()));
        }
    }

    template<class Tp, class Alloc>
    inline
    list<Tp, Alloc>& list<Tp, Alloc>::operator=(list&& __c) noexcept {
        __move_assign(__c, integral_constant<bool, _node_alloc_traits::propagate_on_container_move_assignment::value>());
        return *this;
    }

    template<class Tp, class Alloc>
    void list<Tp, Alloc>::__move_assign(list& __c, false_type) {
        if (base::__node_alloc() != __c.__node_alloc()) {
            using _Ip = std::move_iterator<iterator>;
            assign(_Ip(__c.begin()), _Ip(__c.end()));
        }
        else
            __move_assign(__c, true_type);
    }

    template<class Tp, class Alloc>
    void
    list<Tp, Alloc>::__move_assign(list& __c, true_type) noexcept {
        clear();
        base::_move_assign_alloc(__c);
        splice(end(), __c);
    }

    template<class Tp, class Alloc>
    template<class _InpIter>
    void list<Tp, Alloc>::assign(_InpIter __f, _InpIter __l, typename enable_if<is_input_iterator<_InpIter>::value>::type*) {
        iterator __i = begin();
        iterator __e = end();
        for (; __f != __l && __i != __e; ++__f, ++__i)
            *__i = *__f;
        if (__i == __e)
            insert(__e, __f, __l);
        else
            erase(__i, __e);
    }

    template<class Tp, class Alloc>
    void list<Tp, Alloc>::assign(size_type __n, const value_type& __x) {
        iterator __i = begin();
        iterator __e = end();
        for (; __n > 0 && __i != __e; --__n, ++__i)
            *__i = __x;
        if (__i == __e)
            insert(__e, __n, __x);
        else
            erase(__i, __e);
    }

    template<class Tp, class Alloc>
    inline
    Alloc
    list<Tp, Alloc>::getAllocator() const noexcept {
        return allocator_type(base::__node_alloc());
    }

    template<class Tp, class Alloc>
    typename list<Tp, Alloc>::iterator
    list<Tp, Alloc>::insert(const_iterator __p, const value_type& __x) {
        _node_allocator& __na = base::__node_alloc();
        using _Dp = __allocator_destructor<_node_allocator>;
        unique_ptr<_node, _Dp> __hold(_node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        __hold->_prev = 0;
        _node_alloc_traits::construct(__na, std::addressof(__hold->_value), __x);
        __link_nodes(__p._ptr, __hold.get(), __hold.get());
        ++base::__sz();
        return iterator(__hold.release());
    }

    template<class Tp, class Alloc>
    typename list<Tp, Alloc>::iterator
    list<Tp, Alloc>::insert(const_iterator __p, size_type __n, const value_type& __x) {
        iterator __r(__p._ptr);
        if (__n > 0) {
            size_type __ds = 0;
            _node_allocator& __na = base::__node_alloc();
            using _Dp = __allocator_destructor<_node_allocator>;
            unique_ptr<_node, _Dp> __hold(_node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
            __hold->_prev = 0;
            _node_alloc_traits::construct(__na, std::addressof(__hold->_value), __x);
            ++__ds;
            __r = iterator(__hold.get());
            __hold.release();
            iterator __e = __r;
            try {
                for (--__n; __n != 0; --__n, ++__e, ++__ds) {
                    __hold.reset(_node_alloc_traits::allocate(__na, 1));
                    _node_alloc_traits::construct(__na, std::addressof(__hold->_value), __x);
                    __e._ptr->_next = __hold.get();
                    __hold->_prev = __e._ptr;
                    __hold.release();
                }
            }
            catch (...) {
                while (true) {
                    _node_alloc_traits::destroy(__na, std::addressof(*__e));
                    _node_pointer __prev = __e._ptr->_prev;
                    _node_alloc_traits::deallocate(__na, __e._ptr, 1);
                    if (__prev == 0)
                        break;
                    __e = iterator(__prev);
                }
                throw;
            }
            __link_nodes(__p._ptr, __r._ptr, __e._ptr);
            base::__sz() += __ds;
        }
        return __r;
    }

    template<class Tp, class Alloc>
    template<class _InpIter>
    typename list<Tp, Alloc>::iterator
    list<Tp, Alloc>::insert(const_iterator __p, _InpIter __f, _InpIter __l,
                            typename enable_if<is_input_iterator<_InpIter>::value>::type*) {
        iterator __r(__p._ptr);
        if (__f != __l) {
            size_type __ds = 0;
            _node_allocator& __na = base::__node_alloc();
            using _Dp = __allocator_destructor<_node_allocator>;
            unique_ptr<_node, _Dp> __hold(_node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
            __hold->_prev = 0;
            _node_alloc_traits::construct(__na, std::addressof(__hold->_value), *__f);
            ++__ds;
            __r = iterator(__hold.get());
            __hold.release();
            iterator __e = __r;
            try {
                for (++__f; __f != __l; ++__f, (void) ++__e, (void) ++__ds) {
                    __hold.reset(_node_alloc_traits::allocate(__na, 1));
                    _node_alloc_traits::construct(__na, std::addressof(__hold->_value), *__f);
                    __e._ptr->_next = __hold.get();
                    __hold->_prev = __e._ptr;
                    __hold.release();
                }
            }
            catch (...) {
                while (true) {
                    _node_alloc_traits::destroy(__na, std::addressof(*__e));
                    _node_pointer __prev = __e._ptr->_prev;
                    _node_alloc_traits::deallocate(__na, __e._ptr, 1);
                    if (__prev == 0)
                        break;
                    __e = iterator(__prev);
                }
                throw;
            }
            __link_nodes(__p._ptr, __r._ptr, __e._ptr);
            base::__sz() += __ds;
        }
        return __r;
    }

    template<class Tp, class Alloc>
    void
    list<Tp, Alloc>::push_front(const value_type& __x) {
        _node_allocator& __na = base::__node_alloc();
        using _Dp = __allocator_destructor<_node_allocator>;
        unique_ptr<_node, _Dp> __hold(_node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        _node_alloc_traits::construct(__na, std::addressof(__hold->_value), __x);
        __link_nodes_at_front(__hold.get(), __hold.get());
        ++base::__sz();
        __hold.release();
    }

    template<class Tp, class Alloc>
    void
    list<Tp, Alloc>::push_back(const value_type& __x) {
        _node_allocator& __na = base::__node_alloc();
        using _Dp = __allocator_destructor<_node_allocator>;
        unique_ptr<_node, _Dp> __hold(_node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        _node_alloc_traits::construct(__na, std::addressof(__hold->_value), __x);
        __link_nodes_at_back(__hold.get(), __hold.get());
        ++base::__sz();
        __hold.release();
    }

    template<class Tp, class Alloc>
    void
    list<Tp, Alloc>::push_front(value_type&& __x) {
        _node_allocator& __na = base::__node_alloc();
        using _Dp = __allocator_destructor<_node_allocator>;
        unique_ptr<_node, _Dp> __hold(_node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        _node_alloc_traits::construct(__na, std::addressof(__hold->_value), std::move(__x));
        __link_nodes_at_front(__hold.get(), __hold.get());
        ++base::__sz();
        __hold.release();
    }

    template<class Tp, class Alloc>
    void
    list<Tp, Alloc>::push_back(value_type&& __x) {
        _node_allocator& __na = base::__node_alloc();
        using _Dp = __allocator_destructor<_node_allocator>;
        unique_ptr<_node, _Dp> __hold(_node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        _node_alloc_traits::construct(__na, std::addressof(__hold->_value), std::move(__x));
        __link_nodes_at_back(__hold.get(), __hold.get());
        ++base::__sz();
        __hold.release();
    }

    template<class Tp, class Alloc>
    template<class... _Args>
    void
    list<Tp, Alloc>::emplace_front(_Args&& ... __args) {
        _node_allocator& __na = base::__node_alloc();
        using _Dp = __allocator_destructor<_node_allocator>;
        unique_ptr<_node, _Dp> __hold(_node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        _node_alloc_traits::construct(__na, std::addressof(__hold->_value), std::forward<_Args>(__args)...);
        __link_nodes_at_front(__hold.get(), __hold.get());
        ++base::__sz();
        __hold.release();
    }

    template<class Tp, class Alloc>
    template<class... _Args>
    void
    list<Tp, Alloc>::emplace_back(_Args&& ... __args) {
        _node_allocator& __na = base::__node_alloc();
        using _Dp = __allocator_destructor<_node_allocator>;
        unique_ptr<_node, _Dp> __hold(_node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        _node_alloc_traits::construct(__na, std::addressof(__hold->_value), std::forward<_Args>(__args)...);
        __link_nodes_at_back(__hold.get(), __hold.get());
        ++base::__sz();
        __hold.release();
    }

    template<class Tp, class Alloc>
    template<class... _Args>
    typename list<Tp, Alloc>::iterator
    list<Tp, Alloc>::emplace(const_iterator __p, _Args&& ... __args) {
        _node_allocator& __na = base::__node_alloc();
        using _Dp = __allocator_destructor<_node_allocator>;
        unique_ptr<_node, _Dp> __hold(_node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        __hold->_prev = 0;
        _node_alloc_traits::construct(__na, std::addressof(__hold->_value), std::forward<_Args>(__args)...);
        __link_nodes(__p._ptr, __hold.get(), __hold.get());
        ++base::__sz();
        return iterator(__hold.release());
    }

    template<class Tp, class Alloc>
    typename list<Tp, Alloc>::iterator
    list<Tp, Alloc>::insert(const_iterator __p, value_type&& __x) {
        _node_allocator& __na = base::__node_alloc();
        using _Dp = __allocator_destructor<_node_allocator>;
        unique_ptr<_node, _Dp> __hold(_node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
        __hold->_prev = 0;
        _node_alloc_traits::construct(__na, std::addressof(__hold->_value), std::move(__x));
        __link_nodes(__p._ptr, __hold.get(), __hold.get());
        ++base::__sz();
        return iterator(__hold.release());
    }

    template<class Tp, class Alloc>
    void
    list<Tp, Alloc>::pop_front() {
        _node_allocator& __na = base::__node_alloc();
        _node_pointer __n = base::_end._next;
        base::__unlink_nodes(__n, __n);
        --base::__sz();
        _node_alloc_traits::destroy(__na, std::addressof(__n->_value));
        _node_alloc_traits::deallocate(__na, __n, 1);
    }

    template<class Tp, class Alloc>
    void
    list<Tp, Alloc>::pop_back() {
        _node_allocator& __na = base::__node_alloc();
        _node_pointer __n = base::_end._prev;
        base::__unlink_nodes(__n, __n);
        --base::__sz();
        _node_alloc_traits::destroy(__na, std::addressof(__n->_value));
        _node_alloc_traits::deallocate(__na, __n, 1);
    }

    template<class Tp, class Alloc>
    typename list<Tp, Alloc>::iterator
    list<Tp, Alloc>::erase(const_iterator __p) {
        _node_allocator& __na = base::__node_alloc();
        _node_pointer __n = __p._ptr;
        _node_pointer __r = __n->_next;
        base::__unlink_nodes(__n, __n);
        --base::__sz();
        _node_alloc_traits::destroy(__na, std::addressof(__n->_value));
        _node_alloc_traits::deallocate(__na, __n, 1);
        return iterator(__r);
    }

    template<class Tp, class Alloc>
    typename list<Tp, Alloc>::iterator
    list<Tp, Alloc>::erase(const_iterator __f, const_iterator __l) {
        if (__f != __l) {
            _node_allocator& __na = base::__node_alloc();
            base::__unlink_nodes(__f._ptr, __l._ptr->_prev);
            while (__f != __l) {
                _node_pointer __n = __f._ptr;
                ++__f;
                --base::__sz();
                _node_alloc_traits::destroy(__na, std::addressof(__n->_value));
                _node_alloc_traits::deallocate(__na, __n, 1);
            }
        }
        return iterator(__l._ptr);
    }

    template<class Tp, class Alloc>
    void
    list<Tp, Alloc>::resize(size_type __n) {
        if (__n < base::__sz())
            erase(__iterator(__n), end());
        else if (__n > base::__sz()) {
            __n -= base::__sz();
            size_type __ds = 0;
            _node_allocator& __na = base::__node_alloc();
            using _Dp = __allocator_destructor<_node_allocator>;
            unique_ptr<_node, _Dp> __hold(_node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
            __hold->_prev = 0;
            _node_alloc_traits::construct(__na, std::addressof(__hold->_value));
            ++__ds;
            iterator __r = iterator(__hold.release());
            iterator __e = __r;
            try {
                for (--__n; __n != 0; --__n, ++__e, ++__ds) {
                    __hold.reset(_node_alloc_traits::allocate(__na, 1));
                    _node_alloc_traits::construct(__na, std::addressof(__hold->_value));
                    __e._ptr->_next = __hold.get();
                    __hold->_prev = __e._ptr;
                    __hold.release();
                }
            }
            catch (...) {
                while (true) {
                    _node_alloc_traits::destroy(__na, std::addressof(*__e));
                    _node_pointer __prev = __e._ptr->_prev;
                    _node_alloc_traits::deallocate(__na, __e._ptr, 1);
                    if (__prev == 0)
                        break;
                    __e = iterator(__prev);
                }
                throw;
            }
            __link_nodes_at_back(__r._ptr, __e._ptr);
            base::__sz() += __ds;
        }
    }

    template<class Tp, class Alloc>
    void
    list<Tp, Alloc>::resize(size_type __n, const value_type& __x) {
        if (__n < base::__sz())
            erase(__iterator(__n), end());
        else if (__n > base::__sz()) {
            __n -= base::__sz();
            size_type __ds = 0;
            _node_allocator& __na = base::__node_alloc();
            using _Dp = __allocator_destructor<_node_allocator>;
            unique_ptr<_node, _Dp> __hold(_node_alloc_traits::allocate(__na, 1), _Dp(__na, 1));
            __hold->_prev = 0;
            _node_alloc_traits::construct(__na, std::addressof(__hold->_value), __x);
            ++__ds;
            iterator __r = iterator(__hold.release());
            iterator __e = __r;
            try {
                for (--__n; __n != 0; --__n, ++__e, ++__ds) {
                    __hold.reset(_node_alloc_traits::allocate(__na, 1));
                    _node_alloc_traits::construct(__na, std::addressof(__hold->_value), __x);
                    __e._ptr->_next = __hold.get();
                    __hold->_prev = __e._ptr;
                    __hold.release();
                }
            }
            catch (...) {
                while (true) {
                    _node_alloc_traits::destroy(__na, std::addressof(*__e));
                    _node_pointer __prev = __e._ptr->_prev;
                    _node_alloc_traits::deallocate(__na, __e._ptr, 1);
                    if (__prev == 0)
                        break;
                    __e = iterator(__prev);
                }
                throw;
            }
            __link_nodes(static_cast<_node_pointer>(std::addressof(base::_end)), __r._ptr, __e._ptr);
            base::__sz() += __ds;
        }
    }

    template<class Tp, class Alloc>
    void
    list<Tp, Alloc>::splice(const_iterator __p, list& __c) {
        if (!__c.empty()) {
            _node_pointer __f = __c._end._next;
            _node_pointer __l = __c._end._prev;
            base::__unlink_nodes(__f, __l);
            __link_nodes(__p._ptr, __f, __l);
            base::__sz() += __c.__sz();
            __c.__sz() = 0;
        }
    }

    template<class Tp, class Alloc>
    void
    list<Tp, Alloc>::splice(const_iterator __p, list& __c, const_iterator __i) {
        if (__p._ptr != __i._ptr && __p._ptr != __i._ptr->_next) {
            _node_pointer __f = __i._ptr;
            base::__unlink_nodes(__f, __f);
            __link_nodes(__p._ptr, __f, __f);
            --__c.__sz();
            ++base::__sz();
        }
    }

    template<class Tp, class Alloc>
    void
    list<Tp, Alloc>::splice(const_iterator __p, list& __c, const_iterator __f, const_iterator __l) {
        if (__f != __l) {
            if (this != &__c) {
                size_type __s = static_cast<size_type>(std::distance(__f, __l));
                __c.__sz() -= __s;
                base::__sz() += __s;
            }
            _node_pointer __first = __f._ptr;
            --__l;
            _node_pointer __last = __l._ptr;
            base::__unlink_nodes(__first, __last);
            __link_nodes(__p._ptr, __first, __last);
        }
    }

    template<class Tp, class Alloc>
    void
    list<Tp, Alloc>::remove(const value_type& __x) {
        list<Tp, Alloc> __deleted_nodes; // collect the nodes we're removing
        for (const_iterator __i = begin(), __e = end(); __i != __e;) {
            if (*__i == __x) {
                const_iterator __j = std::next(__i);
                for (; __j != __e && *__j == __x; ++__j);
                __deleted_nodes.splice(__deleted_nodes.end(), *this, __i, __j);
                __i = __j;
                if (__i != __e)
                    ++__i;
            }
            else
                ++__i;
        }
    }

    template<class Tp, class Alloc>
    template<class _Pred>
    void
    list<Tp, Alloc>::remove_if(_Pred __pred) {
        for (iterator __i = begin(), __e = end(); __i != __e;) {
            if (__pred(*__i)) {
                iterator __j = std::next(__i);
                for (; __j != __e && __pred(*__j); ++__j);
                __i = erase(__i, __j);
                if (__i != __e)
                    ++__i;
            }
            else
                ++__i;
        }
    }

    template<class Tp, class Alloc>
    inline
    void
    list<Tp, Alloc>::unique() {
        unique(std::__equal_to<value_type>());
    }

    template<class Tp, class Alloc>
    template<class _BinaryPred>
    void
    list<Tp, Alloc>::unique(_BinaryPred __binary_pred) {
        for (iterator __i = begin(), __e = end(); __i != __e;) {
            iterator __j = std::next(__i);
            for (; __j != __e && __binary_pred(*__i, *__j); ++__j);
            if (++__i != __j)
                __i = erase(__i, __j);
        }
    }

    template<class Tp, class Alloc>
    inline
    void
    list<Tp, Alloc>::merge(list& __c) {
        merge(__c, std::__less<value_type>());
    }

    template<class Tp, class Alloc>
    template<class _Comp>
    void
    list<Tp, Alloc>::merge(list& __c, _Comp __comp) {
        if (this != &__c) {
            iterator __f1 = begin();
            iterator __e1 = end();
            iterator __f2 = __c.begin();
            iterator __e2 = __c.end();
            while (__f1 != __e1 && __f2 != __e2) {
                if (__comp(*__f2, *__f1)) {
                    size_type __ds = 1;
                    iterator __m2 = std::next(__f2);
                    for (; __m2 != __e2 && __comp(*__m2, *__f1); ++__m2, ++__ds);
                    base::__sz() += __ds;
                    __c.__sz() -= __ds;
                    _node_pointer __f = __f2._ptr;
                    _node_pointer __l = __m2._ptr->_prev;
                    __f2 = __m2;
                    base::__unlink_nodes(__f, __l);
                    __m2 = std::next(__f1);
                    __link_nodes(__f1._ptr, __f, __l);
                    __f1 = __m2;
                }
                else
                    ++__f1;
            }
            splice(__e1, __c);
        }
    }

    template<class Tp, class Alloc>
    inline
    void
    list<Tp, Alloc>::sort() {
        sort(std::__less<value_type>());
    }

    template<class Tp, class Alloc>
    template<class _Comp>
    inline
    void
    list<Tp, Alloc>::sort(_Comp __comp) {
        __sort(begin(), end(), base::__sz(), __comp);
    }

    template<class Tp, class Alloc>
    template<class _Comp>
    typename list<Tp, Alloc>::iterator
    list<Tp, Alloc>::__sort(iterator __f1, iterator __e2, size_type __n, _Comp& __comp) {
        switch (__n) {
            case 0:
            case 1:
                return __f1;
            case 2:
                if (__comp(*--__e2, *__f1)) {
                    _node_pointer __f = __e2._ptr;
                    base::__unlink_nodes(__f, __f);
                    __link_nodes(__f1._ptr, __f, __f);
                    return __e2;
                }
                return __f1;
        }
        size_type __n2 = __n / 2;
        iterator __e1 = std::next(__f1, __n2);
        iterator __r = __f1 = __sort(__f1, __e1, __n2, __comp);
        iterator __f2 = __e1 = __sort(__e1, __e2, __n - __n2, __comp);
        if (__comp(*__f2, *__f1)) {
            iterator __m2 = std::next(__f2);
            for (; __m2 != __e2 && __comp(*__m2, *__f1); ++__m2);
            _node_pointer __f = __f2._ptr;
            _node_pointer __l = __m2._ptr->_prev;
            __r = __f2;
            __e1 = __f2 = __m2;
            base::__unlink_nodes(__f, __l);
            __m2 = std::next(__f1);
            __link_nodes(__f1._ptr, __f, __l);
            __f1 = __m2;
        }
        else
            ++__f1;
        while (__f1 != __e1 && __f2 != __e2) {
            if (__comp(*__f2, *__f1)) {
                iterator __m2 = std::next(__f2);
                for (; __m2 != __e2 && __comp(*__m2, *__f1); ++__m2);
                _node_pointer __f = __f2._ptr;
                _node_pointer __l = __m2._ptr->_prev;
                if (__e1 == __f2)
                    __e1 = __m2;
                __f2 = __m2;
                base::__unlink_nodes(__f, __l);
                __m2 = std::next(__f1);
                __link_nodes(__f1._ptr, __f, __l);
                __f1 = __m2;
            }
            else
                ++__f1;
        }
        return __r;
    }

    template<class Tp, class Alloc>
    void
    list<Tp, Alloc>::reverse() noexcept {
        if (base::__sz() > 1) {
            iterator __e = end();
            for (iterator __i = begin(); __i._ptr != __e._ptr;) {
                std::swap(__i._ptr->_prev, __i._ptr->_next);
                __i._ptr = __i._ptr->_prev;
            }
            std::swap(__e._ptr->_prev, __e._ptr->_next);
        }
    }

    template<class Tp, class Alloc>
    bool
    list<Tp, Alloc>::__invariants() const {
        return size() == std::distance(begin(), end());
    }

    template<class Tp, class Alloc>
    inline
    bool
    operator==(const list<Tp, Alloc>& __x, const list<Tp, Alloc>& __y) {
        return __x.size() == __y.size() && std::equal(__x.begin(), __x.end(), __y.begin());
    }

    template<class Tp, class Alloc>
    inline
    bool
    operator<(const list<Tp, Alloc>& __x, const list<Tp, Alloc>& __y) {
        return std::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
    }

    template<class Tp, class Alloc>
    inline
    bool
    operator!=(const list<Tp, Alloc>& __x, const list<Tp, Alloc>& __y) {
        return !(__x == __y);
    }

    template<class Tp, class Alloc>
    inline
    bool
    operator>(const list<Tp, Alloc>& __x, const list<Tp, Alloc>& __y) {
        return __y < __x;
    }

    template<class Tp, class Alloc>
    inline
    bool
    operator>=(const list<Tp, Alloc>& __x, const list<Tp, Alloc>& __y) {
        return !(__x < __y);
    }

    template<class Tp, class Alloc>
    inline
    bool
    operator<=(const list<Tp, Alloc>& __x, const list<Tp, Alloc>& __y) {
        return !(__y < __x);
    }

    template<class Tp, class Alloc>
    inline
    void
    swap(list<Tp, Alloc>& __x, list<Tp, Alloc>& __y)

    noexcept(noexcept(__x.swap(__y))) {
        __x.swap(__y);
    }

}

#endif  // _LIBCPP_LIST
