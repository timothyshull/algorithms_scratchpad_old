#ifndef CUSTOM_ALGORITHMS_ALLOCATOR_H
#define CUSTOM_ALGORITHMS_ALLOCATOR_H

#include <cstddef>
#include <type_traits>
#include <memory>

template<class T>
class allocator {
public:
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using value_type = T;

    using propagate_on_container_move_assignment = std::true_type;
    using is_always_equal = std::true_type;

    template<class U>
    struct rebind {
        typedef allocator<U> other;
    };

    allocator() {}

    template<class U>
    allocator(const allocator<U> &) noexcept {}

    pointer address(reference x) const noexcept { return std::addressof(x); }

    const_pointer address(const_reference x) const noexcept { return std::addressof(x); }

    pointer allocate(size_type n, allocator<void>::const_pointer = nullptr) {
        return static_cast<pointer>(::operator new(n * sizeof(T)));
    }

    void deallocate(pointer p, size_type) noexcept { ::operator delete((void *) p); }

    size_type max_size() const noexcept { return size_type(~0) / sizeof(T); }

    template<class U, class... Args>
    void construct(U *p, Args &&... args) {
        ::new((void *) p) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) { p->~T(); }
};

#endif //CUSTOM_ALGORITHMS_ALLOCATOR_H
