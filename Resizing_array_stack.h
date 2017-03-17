#ifndef CH_1_3_RESIZING_ARRAY_STACK_H
#define CH_1_3_RESIZING_ARRAY_STACK_H

#include <iterator>
#include <memory>
#include <stdexcept>
#include "utility.h"

template <typename T>
class Resizing_array_stack;

template <typename T>
struct Resizing_array_stack_traits {
    using stack_type = Resizing_array_stack<T>;
    using stack_reference = stack_type &;
    using stack_pointer = stack_type *;
    using index_type = std::size_t;
};

class Empty_stack_iterator_exception : public std::runtime_error {
public:
    inline explicit Empty_stack_iterator_exception(const std::string &s) : std::runtime_error{s} {}

    inline explicit Empty_stack_iterator_exception(const char *s) : std::runtime_error{s} {}

    virtual ~Empty_stack_iterator_exception() noexcept {};
};

template<typename T>
class Resizing_array_stack_iterator {
    using stack_traits = Resizing_array_stack_traits<T>;
    using index_type = typename stack_traits::index_type;
    using stack_type = typename stack_traits::stack_type;
    using stack_reference = typename stack_traits::stack_reference;
    using stack_pointer = typename stack_traits::stack_pointer;
    
    index_type index_;
    stack_pointer stack_;

    template<class>
    friend
    class Resizing_array_stack;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using reference = value_type &;
    using pointer = value_type *;  // reconsider this
    using size_type = std::size_t;
    using difference_type = typename std::pointer_traits<pointer>::difference_type;

    inline Resizing_array_stack_iterator() noexcept : index_{0}, stack_{nullptr} {}

    inline explicit Resizing_array_stack_iterator(stack_reference s) noexcept : index_{s.size()}, stack_{&s} {}

    inline explicit Resizing_array_stack_iterator(stack_reference s, size_type index) noexcept : index_{index}, stack_{&s} {}

    inline reference operator*() const {
        if (stack_ == nullptr) {
            throw Empty_stack_iterator_exception("The iterator's stack has not been set");
        }
        return stack_->elements_[index_ - 1];
    }

    // Need to handle index = 0
    inline pointer operator->() const {
        return std::pointer_traits<pointer>::pointer_to(stack_->elements_[index_ - 1]);
    }

    // hides that it is a reverse iterator
    inline Resizing_array_stack_iterator &operator++() {
        index_--;
        return *this;
    }

    inline Resizing_array_stack_iterator operator++(int) {
        Resizing_array_stack_iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    friend
    inline bool operator==(const Resizing_array_stack_iterator &x, const Resizing_array_stack_iterator &y) { return x.index_ == y.index_ && x.stack_ == y.stack_; }

    friend
    inline bool operator!=(const Resizing_array_stack_iterator &x, const Resizing_array_stack_iterator &y) { return !(x == y); }
};

template <typename T>
class Resizing_array_stack {
public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using pointer = value_type *;
    using array_type = value_type *;
    using const_pointer = value_type const *;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using iterator = Resizing_array_stack_iterator<value_type>;

private:
    array_type elements_;
    size_type max_{25};
    size_type size_;

    template <class>
    friend
    class Resizing_array_stack_iterator;

    void _resize(size_type max) {
        elements_ = utility::resize<value_type>(elements_, size_, max);
        max_ = max;
    }

public:
    inline Resizing_array_stack() : size_{0} { _resize(max_); }

    inline bool empty() { return size_ == 0; }

    inline size_type size() { return size_; }

    inline iterator begin() noexcept { return iterator{*this}; }

    inline iterator end() noexcept { return iterator{*this, 0}; }

    void push(reference item) {
        if (size_ == max_) {
            _resize(2 * max_);
        }
        elements_[size_] = item;
        size_++;
    }

    value_type pop() {
        size_--;
        value_type tmp = elements_[size_];
        if (size_ > 0 && size_ == max_ / 4) {
            _resize(max_ / 2);
        }
        return tmp;
    }
};

#endif //CH_1_3_RESIZING_ARRAY_STACK_H
