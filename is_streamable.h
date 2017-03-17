#ifndef CUSTOM_ALGORITHMS_IS_STREAMABLE_H
#define CUSTOM_ALGORITHMS_IS_STREAMABLE_H

#include <type_traits>

namespace __is_streamable_imp {
    using __one = char;
    struct __two {
        char l[2];
    };

    template<typename S, typename T>
    __one is_streamable_test(int T::*) -> decltype(std::declval<S &>() << std::declval<T>());

    template<typename, typename>
    __two is_streamable_test(...);
}

template<typename S, typename T>
struct is_streamable : public std::integral_constant<bool,
        sizeof(__is_streamable_imp::is_streamable_test<S, T>(0)) == 1> {
};


//template<typename S, typename T>
//struct is_streamable {
//    template<typename Str, typename Tp>
//    static auto test(int) -> decltype(std::declval<Str &>() << std::declval<Tp>(), std::true_type()) {};
//
//    template<typename, typename>
//    static auto test(...) -> std::false_type {};
//
//public:
////    static const bool value = decltype(test<S, T>(0))::value;
//    static const bool value = (sizeof(test<S, T>(0) == 1));
//};

#endif //CUSTOM_ALGORITHMS_IS_STREAMABLE_H
