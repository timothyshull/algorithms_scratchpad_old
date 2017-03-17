#ifndef CPP_DATA_STRUCTURES_LIST_H
#define CPP_DATA_STRUCTURES_LIST_H

#include <memory>

using std::allocator;

namespace simple_algos {
    template<typename Tp>
    struct list_node;

    template<typename Tp>
    struct list_node_base {
        using pointer = Tp*;
        using base_pointer = list_node_base*;

        pointer _prev;
        pointer _next;

        list_node_base() : _prev{_self()}, _next{_self()} { }

        pointer _self() {
            return static_cast<pointer>(std::addressof(this));
        }
    };

    template<typename Tp>
    struct list_node : public list_node_base<Tp> {
        Tp _value;
    };

    template<typename Tp, typename Alloc = allocator<Tp> >
    class list;

    template<typename Tp, typename Alloc = allocator<Tp> >
    class list_imp;

    template<typename Tp>
    class list_const_iterator;

    template<typename Tp>
    class list_iterator {
        using node_pointer = typename list_node<Tp>*;

        node_pointer _ptr;

        explicit list_iterator(node_pointer _p) noexcept : _ptr{_p} { }

        template<typename, typename> friend
        class list;

        template<typename, typename> friend
        class list_imp;

        template<typename, typename> friend
        class list_const_iterator;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = Tp;
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = ptrdiff_t;

        list_iterator() noexcept : _ptr{nullptr} { }

        reference operator*() const {
            return _ptr->_value;
        }

        pointer operator->() const {
            return _ptr->_value;
        }

        list_iterator& operator++() {
            _ptr = _ptr->_next;
            return *this;
        }

        list_iterator operator++(int) {
            list_iterator it(*this);
            ++(*this);
            return it;
        }

        list_iterator& operator--() {
            _ptr = _ptr->_prev;
            return *this;
        }

        list_iterator operator--(int) {
            list_iterator it(*this);
            --(*this);
            return it;
        }

        friend bool operator==(const list_iterator& x, const list_iterator& y) {
            return x._ptr == y._ptr;
        }

        friend bool operator!=(const list_iterator& x, const list_iterator& y) {
            return !(x == y);
        }

        template<typename Tp>
        class list_const_iterator {
            using node_pointer = typename list_node<Tp>*;

            node_pointer _ptr;

            explicit list_const_iterator(node_pointer _p) noexcept : _ptr{_p} { }

            template<typename, typename> friend
            class list;

            template<typename, typename> friend
            class list_imp;

            template<typename, typename> friend
            class list_const_iterator;

        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = Tp;
            using reference = const value_type&;
            using pointer = const value_type*;
            using difference_type = ptrdiff_t;

            list_const_iterator() noexcept : _ptr{nullptr} { }

            list_const_iterator(const list_iterator<Tp>& it) noexcept : _ptr{it._ptr} {}

            reference operator*() const {
                return _ptr->_value;
            }

            pointer operator->() const {
                return _ptr->_value;
            }

            list_const_iterator& operator++() {
                _ptr = _ptr->_next;
                return *this;
            }

            list_const_iterator operator++(int) {
                list_const_iterator it(*this);
                ++(*this);
                return it;
            }

            list_const_iterator& operator--() {
                _ptr = _ptr->_prev;
                return *this;
            }

            list_const_iterator operator--(int) {
                list_const_iterator it(*this);
                --(*this);
                return it;
            }

            friend bool operator==(const list_const_iterator& x, const list_const_iterator& y) {
                return x._ptr == y._ptr;
            }

            friend bool operator!=(const list_const_iterator& x, const list_const_iterator& y) {
                return !(x == y);
            }
        };
    };
};

#endif //CPP_DATA_STRUCTURES_LIST_H
