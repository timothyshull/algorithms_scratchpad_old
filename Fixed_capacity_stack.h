#ifndef CH_1_3_FIXED_CAPACITY_STACK_H
#define CH_1_3_FIXED_CAPACITY_STACK_H

#include <cstddef>
#include <new>
#include <stdexcept>
#include <string>
#include <iostream>

#include "utility.h"

class Bad_fcs_array : public std::runtime_error {
public:
    inline explicit Bad_fcs_array(const std::string &s) : std::runtime_error{s} {}

    inline explicit Bad_fcs_array(const char *s) : std::runtime_error{s} {}

    virtual ~Bad_fcs_array() noexcept {};
};

template<typename T>
class Fixed_capacity_stack {
    T *a;
    size_t n;

public:
    using value_type = T;
    using reference = T &;

    explicit Fixed_capacity_stack(size_t cap) : a{new(std::nothrow) T[cap]}, n{0} {}

    inline bool empty() { return n == 0; }

    inline size_t size() { return n; }

    void push(reference item) {
        if (a == nullptr) {
            throw Bad_fcs_array("Unable to reserve memory for the underlying array");
        }
        a[n] = item;
        n++;
    }

    value_type pop() {
        n--;
        return a[n];
    }
};

template <>
class Fixed_capacity_stack<void> {
public:
    static void main() {
        Fixed_capacity_stack<std::string> s{100};
        for (std::string item; std::getline(std::cin, item) && item != "";) {
            if (item != "-") {
                s.push(item);
            } else if (!s.empty()) {
                std::cout << s.pop() << "\n";
            } else {
                break;
            }
        }
        std::cout << "(" << s.size() << " remaining on the stack)\n";
    }
};

#endif //CH_1_3_FIXED_CAPACITY_STACK_H
