#ifndef ALGS_CPP_ITEM_ADT_H
#define ALGS_CPP_ITEM_ADT_H

#include <cstdlib>
#include <iostream>

static int maxKey = 1000;
using Key = int;

template<typename T>
class Item {
private:
    Key keyval;
    T data;
public:
    Item() : keyval{maxKey} { }

    Key key() {
        return keyval;
    }

    int null() {
        return keyval == maxKey;
    }

    void rand() {
        keyval = 1000 * ::rand() / RAND_MAX;
        data = static_cast<T>(1.0 * ::rand() / RAND_MAX);
    }

    int scan(std::istream &is = std::cin) {
        return (is >> keyval >> data) != 0;
    }

    void show(std::ostream &os = std::cout) {
        os << keyval << " " << data << std::endl;
    }
};

std::ostream &operator<<(std::ostream &os, Item &x) {
    x.show(os);
    return os;
}

#endif //ALGS_CPP_ITEM_ADT_H
