#ifndef CUSTOM_ALGORITHMS_MAKE_UNIQUE_H
#define CUSTOM_ALGORITHMS_MAKE_UNIQUE_H

#include <cstddef>
#include <memory>

template<class T>
struct unique_if {
    using unique_single = std::unique_ptr<T>;
};

template<class T>
struct unique_if<T[]> {
    using unique_array_unknown_bound = std::unique_ptr<T[]>;
};

template<class T, size_t N>
struct unique_if<T[N]> {
    using unique_array_known_bound = void;
};

template<class T, class... Args>
inline typename unique_if<T>::unique_single
make_unique(Args &&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<class T>
inline typename
unique_if<T>::unique_array_unknown_bound
make_unique(size_t n) {
    typedef typename std::remove_extent<T>::type Up;
    return std::unique_ptr<T>(new Up[n]());
}

#endif //CUSTOM_ALGORITHMS_MAKE_UNIQUE_H
