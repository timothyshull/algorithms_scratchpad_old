#ifndef SIMPLE_CPP_ALGOS_BAG_H
#define SIMPLE_CPP_ALGOS_BAG_H

#include <cstddef>
#include <iterator>

namespace simple_algos {
    template<typename Tp>
    class queue;

    template<typename Tp>
    struct queue_node {
        using value_type = Tp;
        using pointer = queue_node<Tp>*;

        value_type _value;
        pointer _next;
    };

    template<typename Tp>
    class queue_iterator {
    public:
        using node_pointer = queue_node<Tp>*;
        node_pointer _ptr;

        explicit queue_iterator(node_pointer _p) noexcept : _ptr{_p} { }

        template<typename> friend
        class queue;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Tp;
        using reference = Tp&;
        using pointer = Tp*;
        using difference_type = ptrdiff_t;

        queue_iterator() noexcept : _ptr{nullptr} { }

        reference operator*() const {
            return _ptr->_value;
        }

        pointer operator->() const {
            return std::addressof(_ptr->_value);
        }

        queue_iterator& operator++() {
            _ptr = _ptr->_next;
            return *this;
        }

        queue_iterator operator++(int) {
            queue_iterator __t(*this);
            ++(*this);
            return __t;
        }

        friend
        bool operator==(const queue_iterator& __x, const queue_iterator& __y) {
            return __x._ptr == __y._ptr;
        }

        friend
        bool operator!=(const queue_iterator& __x, const queue_iterator& __y) { return !(__x == __y); }
    };

    template<typename Tp>
    class queue {
    public:
        using value_type = Tp;
        using pointer = Tp*;
        using reference = Tp&;
        using node = queue_node<Tp>;
        using node_pointer = queue_node<Tp>*;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using iterator = queue_iterator<value_type>;

        queue() noexcept : _first{nullptr}, _size{0} { }

        ~queue() {
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

        value_type peek() {
            if (empty())
                throw;
            return _first->_value;
        }

        void enqueue(value_type _n) {
            node_pointer old = _last;
            _last = new queue_node<value_type>{_n};
            if (empty())
                _first = _last;
            else
                old->_next = _last;
            _size += 1;
        }

        void dequeue() {
            if (empty())
                throw;
            value_type _i = _first->_value;
            _first = _first->_next;
            _size -= 1;
            if (empty())
                _last = nullptr;
            return _i;
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
        node_pointer _last;
        size_type _size;
    };
}

#endif //SIMPLE_CPP_ALGOS_BAG_H
