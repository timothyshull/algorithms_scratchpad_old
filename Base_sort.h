#ifndef CH_2_1_GENERIC_SORT_INTERFACE_H
#define CH_2_1_GENERIC_SORT_INTERFACE_H

#include <string>
#include <vector>
#include <cassert>
#include <iostream>

template<typename Comparable>
class Base_sort {
public:
    virtual void sort(std::vector<Comparable> &a) = 0;

protected:
    inline static bool less(Comparable &v, Comparable &w) {
        return v < w;
    }

    static void exch(std::vector<Comparable> &a, int i, int j) {
        std::swap(a[i], a[j]);
    }

    static void show(std::vector<Comparable> &a) {
        for (auto x : a) {
            std::cout << x << "\n";
        }
    }

public:
    virtual bool is_sorted(std::vector<Comparable> &a) {
        for (int i = 1; i < a.size(); i++) {
            if (less(a[i], a[i - 1])) { return false; }
        }
        return true;
    }

//    virtual void main() {  // Read strings from standard input, sort them, and print.
//        std::vector<std::string> a;
//
//        for (std::string line; std::getline(std::cin, line) && line != "";) {
//            a.emplace_back(line);
//        }
//
//        sort(a);
//        assert(is_sorted(a));
//        show(a);
//    }
};

#endif //CH_2_1_GENERIC_SORT_INTERFACE_H
