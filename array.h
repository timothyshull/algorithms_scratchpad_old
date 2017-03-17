#ifndef CUSTOM_ALGORITHMS_ARRAY_H
#define CUSTOM_ALGORITHMS_ARRAY_H

#include <cstddef>
#include <iterator>
#include <stdexcept>

template<typename T, size_t Sz>
class custom_array {
public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = value_type *;
    using const_iterator = const value_type *;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    value_type elems_[Sz > 0 ? Sz : 1];

public:
    void fill(const_reference value) {
        int n = static_cast<int>(Sz);
        pointer first = elems_;
        for (; n > 0; ++first, --n)
            *first = value;
    }

    void swap(custom_array &a) {
        pointer current1 = elems_;
        pointer current2 = a.elems_;
        pointer last = elems_ + Sz;
        for (; current1 != last; ++current1, ++current2) {
            std::swap(*current1, *current2);
        }
    }

    // iterators:
    iterator begin() { return iterator(elems_); }

    const_iterator begin() const { return const_iterator(elems_); }

    iterator end() { return iterator(elems_ + Sz); }

    const_iterator end() const { return const_iterator(elems_ + Sz); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

    reverse_iterator rend() { return reverse_iterator(begin()); }

    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    const_iterator cbegin() const { return begin(); }

    const_iterator cend() const { return end(); }

    const_reverse_iterator crbegin() const { return rbegin(); }

    const_reverse_iterator crend() const { return rend(); }

    // capacity:
    size_type size() const { return Sz; }

    size_type max_size() const { return Sz; }

    bool empty() const { return Sz == 0; }


    // element access:
    reference operator[](size_type n) { return elems_[n]; }

    constexpr const_reference operator[](size_type n) const { return elems_[n]; }

    reference at(size_type n) {
        if (n >= Sz) {
            throw std::out_of_range("custom_array::at");
        }
        return elems_[n];
    };

    constexpr const_reference at(size_type n) const {
        if (n >= Sz) {
            throw std::out_of_range("custom_array::at");
        }
        return elems_[n];
    };

    reference front() { return elems_[0]; }

    constexpr const_reference front() const { return elems_[0]; }

    reference back() { return elems_[Sz > 0 ? Sz - 1 : 0]; }

    constexpr const_reference back() const { return elems_[Sz > 0 ? Sz - 1 : 0]; }

    value_type *data() { return elems_; }

    const value_type *data() const { return elems_; }

};

#endif //CUSTOM_ALGORITHMS_ARRAY_H
