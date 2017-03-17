#ifndef SIMPLE_CPP_ALGOS_BAG_H
#define SIMPLE_CPP_ALGOS_BAG_H

#include <cstddef>
//#include <iterator>

namespace simple_algos {
    template<typename Tp>
    class bag;

    template<typename Tp>
    struct bag_node {
        using value_type = Tp;
        using pointer = bag_node<Tp>*;

        value_type _value;
        pointer _next;
    };

    template<typename Tp>
    class bag_iterator {
    public:
        using node_pointer = bag_node<Tp>*;
        node_pointer _ptr;

        explicit bag_iterator(node_pointer _p) noexcept : _ptr{_p} { }

        template<typename> friend
        class bag;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Tp;
        using reference = Tp&;
        using pointer = Tp*;
        using difference_type = ptrdiff_t;

        bag_iterator() noexcept : _ptr{nullptr} { }

        reference operator*() const {
            return _ptr->_value;
        }

        pointer operator->() const {
            return std::addressof(_ptr->_value);
        }

        bag_iterator& operator++() {
            _ptr = _ptr->_next;
            return *this;
        }

        bag_iterator operator++(int) {
            bag_iterator __t(*this);
            ++(*this);
            return __t;
        }

        friend
        bool operator==(const bag_iterator& __x, const bag_iterator& __y) {
            return __x._ptr == __y._ptr;
        }

        friend
        bool operator!=(const bag_iterator& __x, const bag_iterator& __y) { return !(__x == __y); }
    };

    template<typename Tp>
    class bag {
    public:
        using value_type = Tp;
        using pointer = Tp*;
        using reference = Tp&;
        using node = bag_node<Tp>;
        using node_pointer = bag_node<Tp>*;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using iterator = bag_iterator<value_type>;

        bag() noexcept : _first{nullptr}, _size{0} { }

        ~bag() {
            _destroy_all();
        }

        inline bool empty() const noexcept {
            return _size == 0;
        }

        inline size_type size() noexcept {
            return _size;
        }

        virtual iterator begin() noexcept {
            return iterator{_first};
        }

        virtual iterator end() noexcept {
            return iterator();
        }

        void add(value_type _n) {
            node_pointer old = _first;
            _first = new bag_node<value_type>{_n};
            _first->_next = old;
            _size += 1;
        }

    private:
        void _destroy_all() noexcept {
            if (!empty()) {
                node_pointer _f = _first;
                node_pointer _n = _first->_next;
                while (_n != nullptr) {
                    ::operator delete(_f);
                    _f = _n;
                    _n = _f->_next;
                }
                _size = 0;
            }
        }

        node_pointer _first;
        size_type _size;
    };
}

#endif //SIMPLE_CPP_ALGOS_BAG_H
