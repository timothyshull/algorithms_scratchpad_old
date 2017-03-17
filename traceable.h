#ifndef CUSTOM_ALGORITHMS_TRACEABLE_H
#define CUSTOM_ALGORITHMS_TRACEABLE_H

#include "is_streamable.h"
#include <iosfwd>
//#include <sys/trace.h>
#include <iostream>
#include <type_traits>
#include <ctime>

template<class T>
class traceable {
public:
    using value_type = T;

    traceable() : value_{T()}, timer_{time(nullptr)} {
//        if (is_streamable<decltype(std::cout), T>::value == std::true_type()) {
//            std::cout << "initializing type " << typeid(T) << ": " << value_ << std::endl;
//        } else {
//            std::cout << "initializing type " << typeid(T) << std::endl;
//        }
    };

    traceable(const traceable &t) : value_{t.value_}, timer_{time(nullptr)} {
//        if (is_streamable<decltype(std::cout), T>::value == std::true_type()) {
//            std::cout << "initializing type " << typeid(T) << ": " << value_ << std::endl;
//        } else {
//            std::cout << "initializing type " << typeid(T) << std::endl;
//        }
    };

    traceable(const T &val) : value_{val}, timer_{time(nullptr)} {
//        if (is_streamable<decltype(std::cout), T>::value == std::true_type()) {
//            std::cout << "initializing type " << typeid(T) << ": " << value_ << std::endl;
//        } else {
//            std::cout << "initializing type " << typeid(T) << std::endl;
//        }
    };

    ~traceable() {
        if (is_streamable<decltype(std::cout), T>::value == std::true_type()) {
            std::cout << "initializing type " << typeid(T) << ": " << value_ << std::endl;
        } else {
            std::cout << "initializing type " << typeid(T) << std::endl;
        }
        std::cout << "time since initialization: " << time_since_construction() << std::endl;
    };

    bool operator==(const traceable &rhs) const { return true; };

    bool operator!=(const traceable &rhs) const { return true; };

    bool operator>=(const traceable &rhs) const { return true; };

    bool operator<=(const traceable &rhs) const { return true; };

    bool operator>(const traceable &rhs) const { return true; };

    bool operator<(const traceable &rhs) const { return true; };

    traceable &operator=(traceable &rhs) {
        rhs.value_ = this->value_;
        return rhs;
    };

    void print_value() const {
        if (is_streamable<decltype(std::cout), T>::value == std::true_type()) {
            std::cout << value_ << std::endl;
        } else {
            std::cout << "not implemented " << std::endl;
        }
    };

    double time_since_construction() {
        return difftime(timer_, mktime(&tm_));
    }

    friend std::ostream &operator<<<>(std::ostream &lhs, const traceable &rhs);

    friend std::istream &operator>><>(std::istream &lhs, traceable &rhs);

private:
    value_type value_;
    time_t timer_;
    static tm tm_ = {
            0, // tm_sec -> seconds after the minute [0-60]
            0, // tm_min -> minutes after the hour [0-59]
            0, // tm_hour -> hours since midnight [0-23]
            1, // tm_mday -> day of the month [1-31]
            0, // tm_mon -> months since January [0-11]
            100 // tm_year -> years since 1900
    };
};

template<class T>
std::ostream &operator<<(std::ostream &lhs, const traceable<T> &rhs) {
    lhs << rhs.value_;
    return lhs;
}

template<class T>
std::istream &operator>>(std::istream &lhs, traceable<T> &rhs) {
    T originalValue = rhs.value_;
    lhs >> rhs.value_;
    std::cout << "  " << originalValue << " -> " << rhs.value_ << std::endl;
    return lhs;
}

#endif //CUSTOM_ALGORITHMS_TRACEABLE_H
