#ifndef CPP_DATA_STRUCTURES_BAG_H
#define CPP_DATA_STRUCTURES_BAG_H

#include "mem_util.h"

using std::allocator;
using std::allocator_traits;
//using allocator_destructor = std::__allocator_destructor;
using std::unique_ptr;

namespace algos2 {
//    template<typename T, typename VoidPtr>
//    struct bag_node;
    template<typename T>
    struct bag_node;

//    template<typename T, typename VoidPtr>
//    struct bag_node_base<T, VoidPtr> {
//        using pointer = rebind_pointer<VoidPtr, bag_node_base<T, VoidPtr>>::type;
//        using base_pointer = rebind_pointer<VoidPtr, bag_node_base>::type;
//
//        pointer _prev;
//        pointer _next;
//
//        bag_node_base() : _prev{_self()}, _next{_self()} { }
//
//        pointer _self() {
//            return static_cast<pointer>(pointer_traits<base_pointer>::pointer_to(*this));
//        }
//    };

    template<typename T>
    struct bag_node_base {
        using pointer = T*;

//        pointer _prev;
        pointer _next;

//        bag_node_base() : _prev{_self()}, _next{_self()} { }
        bag_node_base() : _next{_self()} { }

        pointer _self() {
            return this;
        }
    };

//    template<typename T, typename VoidPtr>
//    struct bag_node<T, VoidPtr> : public bag_node_base<T, VoidPtr> {
//        T _value;
//    };

    template<typename T>
    struct bag_node : public bag_node_base<T> {
        using value_type = T;
        using pointer = T*;
        value_type _value;
    };

    template<typename T, typename Alloc>
    class bag;

    template<typename T>
    class bag_const_iterator;



//    template<typename T, typename VoidPtr>
//    class bag_iterator;

    template <typename T>
    class bag_iterator {
        template<class> friend class bag;
        template<typename> friend class bag_const_iterator;

        using value_type = typename bag<T, allocator<T>>::value_type;
        using reference = typename bag<T, allocator<T>>::reference;
        using difference_type = typename bag<T, allocator<T>>::difference_type;
        using pointer = typename bag<T, allocator<T>>::pointer;
        using iterator_category = std::forward_iterator_tag;
//        using iterator_category = std::bidrectional_iterator_tag;

        bag_iterator();

        bool operator==(const bag_iterator& rhs) const;
        bool operator!=(const bag_iterator& rhs) const;
        pointer operator->() const;
        reference operator*() const;

        bag_iterator& operator++();
        bag_iterator& operator--();
        bag_iterator operator++(int n);
        bag_iterator operator--(int n);

    private:
        using node_pointer = typename bag<T, allocator<T>>::node_pointer;
        using bag_pointer = typename bag<T, allocator<T>>::pointer;

        bag_iterator(bag_pointer bp, node_pointer np);

        void _point_to_next_node();
        void _point_to_previous_node();

        bag_pointer _bag;
        node_pointer _node;
    };

//    template<typename T, typename VoidPtr>
//    class bag_const_iterator;

    template <typename T>
    class bag_const_iterator {
        template<class> friend class bag;
        template<typename> friend class bag_const_iterator;

        using value_type = typename bag<T, allocator<T>>::value_type;
        using reference = typename bag<T, allocator<T>>::reference;
        using difference_type = typename bag<T, allocator<T>>::difference_type;
        using pointer = typename bag<T, allocator<T>>::pointer;
        using iterator_category = std::forward_iterator_tag;
//        using iterator_category = std::bidrectional_iterator_tag;

        bag_const_iterator();

        bool operator==(const bag_const_iterator& rhs) const;
        bool operator!=(const bag_const_iterator& rhs) const;
        pointer operator->() const;
        reference operator*() const;

        bag_const_iterator& operator++();
        bag_const_iterator& operator--();
        bag_const_iterator operator++(int n);
        bag_const_iterator operator--(int n);

    private:
        using node_pointer = typename bag<T, allocator<T>>::node_pointer;
        using bag_pointer = typename bag<T, allocator<T>>::pointer;

        bag_const_iterator(bag_pointer bp, node_pointer np);

        void _point_to_next_node();
        void _point_to_previous_node();

        bag_pointer _bag;
        node_pointer _node;
    };

    template<typename T, typename Alloc = allocator<T>>
    class bag {
        using value_type = T;
        using allocator_type = Alloc;
        using alloc_traits = allocator_traits<allocator_type>;
        using size_type = typename alloc_traits::size_type;
        using void_pointer = typename alloc_traits::void_pointer;
        using reference = typename allocator_type::reference;
        using const_reference = typename allocator_type::const_reference;
        using pointer = typename alloc_traits::pointer;
        using const_pointer = typename alloc_traits::const_pointer;
//        using iterator = bag_iterator<value_type, void_pointer>;
        using iterator = bag_iterator<value_type>;
        using const_iterator = bag_const_iterator<value_type>;
//        using const_iterator = bag_const_iterator<value_type, void_pointer>;
        using node_base = bag_node_base<value_type>;
//        using node_base = bag_node_base<value_type, void_pointer>;
//        using node = bag_node<value_type, void_pointer>;
        using node = bag_node<value_type>;
        using node_allocator = typename rebind_alloc_helper<alloc_traits, node>::type;
//        using node_alloc_traits = allocator_traits<node_allocator>;
//        using node_pointer = node_alloc_traits::pointer;
        using node_pointer = node*;
//        using node_const_pointer = node_alloc_traits::pointer;
        using node_const_pointer = const node*;
        using difference_type = typename alloc_traits::difference_type;
//        using reverse_iterator<iterator> reverse_iterator;
//        using reverse_iterator<const_iterator> const_reverse_iterator;
    private:
        node_pointer _first;
        size_type _num;
    public:
        bag() : _first{nullptr}, _num{0} { }

        ~bag() {
            node_pointer current = _first;
            while (current != nullptr) {
                node_pointer previous = current;
                // This seems like it should be unnecessary
                current = dynamic_cast<node_pointer>(previous->_next);
                allocator_type::destroy(previous);
                allocator_type::deallocate(previous);
            }

        };

        bool is_empty() {
            return _first == nullptr;
        }

        size_type size() {
            return _num;
        }

        void add(T item) {
            node_pointer old = _first;
            _first = node_pointer{item};
            _first->_next = old;
            _num += 1;
        }

    };
}

#endif //CPP_DATA_STRUCTURES_BAG_H
