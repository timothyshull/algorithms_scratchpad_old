// See pg 998 of C++ Programming Language for a simplified version of allocator


#ifndef ALGORITHMS_ALLOCATOR_H
#define ALGORITHMS_ALLOCATOR_H

#include <stddef.h>

template<typename T>
class allocator {
public:
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using value_type = T;

    template<typename U>
    struct rebind {
        using other = allocator<U>;
    };

    allocator() noexcept { };

    allocator(const allocator&) noexcept { };

    template<typename U>
    allocator(const allocator<U>&) noexcept;

    ~allocator() { };

    pointer address(reference x) const noexcept { };

    const_pointer address(const_reference x) const noexcept { };

    pointer allocate(size_type n, allocator<void>::const_pointer hint = 0) { };

    void deallocate(pointer p, size_type n) { };

    size_type max_size() const noexcept { };

    template<typename U, typename... Args>
    void construct(U* p, Args&&... args) { };

    template<typename U>
    void destroy(U* p) { }; // p-> ̃U()
};
//#include <new>
//#include <bits/functexcept.h>
//
//_GLIBCXX_BEGIN_NAMESPACE(__gnu_cxx)
//
//using std::size_t;
//using std::ptrdiff_t;
//
///**
// *  @brief  An allocator that uses global new, as per [20.4].
// *
// *  This is precisely the allocator defined in the C++ Standard.
// *    - all allocation calls operator new
// *    - all deallocation calls operator delete
// */
//template<typename _Tp>
//class new_allocator {
//public:
//    typedef size_t size_type;
//    typedef ptrdiff_t difference_type;
//    typedef _Tp* pointer;
//    typedef const _Tp* const_pointer;
//    typedef _Tp& reference;
//    typedef const _Tp& const_reference;
//    typedef _Tp value_type;
//
//    template<typename _Tp1>
//    struct rebind {
//        typedef new_allocator<_Tp1> other;
//    };
//
//    new_allocator() throw() { }
//
//    new_allocator(const new_allocator&) throw() { }
//
//    template<typename _Tp1>
//    new_allocator(const new_allocator<_Tp1>&) throw() { }
//
//    ~new_allocator() throw() { }
//
//    pointer address(reference __x) const { return &__x; }
//
//    const_pointer address(const_reference __x) const { return &__x; }
//
//    // NB: __n is permitted to be 0.  The C++ standard says nothing
//    // about what the return value is when __n == 0.
//    pointer allocate(size_type __n, const void* = 0) {
//        if (__builtin_expect(__n > this->max_size(), false))
//            std::__throw_bad_alloc();
//
//        return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
//    }
//
//    // __p is not permitted to be a null pointer.
//    void deallocate(pointer __p, size_type) { ::operator delete(__p); }
//
//    size_type max_size() const throw() { return size_t(-1) / sizeof(_Tp); }
//
//    // _GLIBCXX_RESOLVE_LIB_DEFECTS
//    // 402. wrong new expression in [some_] allocator::construct
//    void construct(pointer __p, const _Tp& __val) { ::new(__p) _Tp(__val); }
//
//    void destroy(pointer __p) { __p->~_Tp(); }
//};
//
//template<typename _Tp>
//inline bool operator==(const new_allocator<_Tp>&, const new_allocator<_Tp>&) { return true; }
//
//template<typename _Tp>
//inline bool operator!=(const new_allocator<_Tp>&, const new_allocator<_Tp>&) { return false; }
//
//_GLIBCXX_END_NAMESPACE

#endif //ALGORITHMS_ALLOCATOR_H
