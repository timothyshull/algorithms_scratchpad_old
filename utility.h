#ifndef CH_1_3_UTILITY_H
#define CH_1_3_UTILITY_H

#include <cstdlib>
#include <cstdio>

#define lassert(x, m) ((x) ? (void)0 : (std::fprintf(stderr, "%s\n", m), std::abort()))

namespace utility {
    void assert(bool test, const char msg[]) {
        lassert(test, msg);
    }

    class No_such_element_exception : public std::range_error {
    public:
        inline explicit No_such_element_exception(const std::string &s) : std::range_error{s} {}

        inline explicit No_such_element_exception(const char *s) : std::range_error{s} {}

        virtual ~No_such_element_exception() noexcept {};
    };

    template<typename Item>
    Item *resize(Item *array, size_t orig_size, size_t new_size) {
        if (new_size < orig_size) {
            return nullptr;
        }

        if (array == nullptr) {
            std::cerr << "Bad array pointer \n";
            return nullptr;
        }

        Item *tmp;
        try {
            tmp = new Item[new_size];
        } catch (std::bad_alloc &e) {
            std::cerr << "bad_alloc: " << e.what() << "\n";
            return nullptr;  // or exit
        }
        // std::memcpy(tmp, array, orig_size);
        for (ptrdiff_t i = 0; i < orig_size; i++) {
            *(tmp + i) = *(array + i);
        }
        return tmp;
    }
}

#endif //CH_1_3_UTILITY_H
