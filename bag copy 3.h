#ifndef SIMPLE_CPP_ALGOS_BAG_H
#define SIMPLE_CPP_ALGOS_BAG_H

#include <cstddef>
#include <memory>

namespace simple_algos {
    template<typename Tp>
    class bag;

    template<typename Tp>
    struct bag_node {
        using value_type = Tp;
        using pointer = bag_node<Tp>*;

        explicit bag_node(value_type _p) noexcept : _value{_p}, _next{nullptr} { }

        value_type _value;
        pointer _next;
    };

    template<typename Tp>
    class bag_iterator {
    public:
        using node_pointer = typename bag_node<Tp>::pointer;
        node_pointer _ptr;

        explicit bag_iterator(node_pointer _p) noexcept : _ptr{_p} { }

        template<typename> friend
        class bag;

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
            bag_iterator _t(*this);
            ++(*this);
            return _t;
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

        friend class bag_iterator<node>;

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
            _first = new bag_node<value_type>(_n);
            _first->_next = old;
            _size += 1;
        }

    private:
        void _destroy_all() noexcept {
            if (!empty()) {
                std::allocator<value_type> _a1;
                std::allocator<node> _a2;
                node_pointer _f = _first;
                size_type _st{1};
                _size = 0;
                while (_f != nullptr) {
                    node_pointer _n = _f;
                    _f = _f->_next;
                    _a1.destroy(std::addressof(_n->_value));
                    _a2.deallocate(_n, _st);
                }
            }
        }

        node_pointer _first;
        size_type _size;
    };
}

#endif //SIMPLE_CPP_ALGOS_BAG_H
