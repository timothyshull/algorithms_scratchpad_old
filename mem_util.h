#ifndef CPP_DATA_STRUCTURES_MEM_UTIL_H
#define CPP_DATA_STRUCTURES_MEM_UTIL_H

#include <memory>

using std::pointer_traits;
using std::allocator_traits;
//using std::integral_constant;

namespace algos2 {
    template<typename From, typename To>
    struct rebind_pointer {
        using type = typename pointer_traits<From>::template rebind<To>;
    };

    template<class Traits, class T>
    struct rebind_alloc_helper {
        using type = typename Traits::template rebind_alloc<T>;
    };

    template<class _Alloc>
    class __allocator_destructor {
        typedef allocator_traits<_Alloc> __alloc_traits;
    public:
        typedef typename __alloc_traits::pointer pointer;
        typedef typename __alloc_traits::size_type size_type;
    private:
        _Alloc& __alloc_;
        size_type __s_;
    public:
        __allocator_destructor(_Alloc& __a, size_type __s) noexcept : __alloc_(__a), __s_(__s) { }

        void operator()(pointer __p) noexcept {
            __alloc_traits::deallocate(__alloc_, __p, __s_);
        }
    };

//    template <typename _Alloc>
//    void __swap_allocator(_Alloc & __a1, _Alloc & __a2, std::true_type) noexcept {
//        using std::swap;
//        swap(__a1, __a2);
//    }
//
//    template <typename _Alloc>
//    void __swap_allocator(_Alloc & __a1, _Alloc & __a2) noexcept {
//        __swap_allocator(__a1, __a2, integral_constant<bool, std::allocator_traits<_Alloc>::propagate_on_container_swap::value>());
//    }
}

#endif //CPP_DATA_STRUCTURES_MEM_UTIL_H
