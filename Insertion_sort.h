#ifndef CH_2_1_INSERTION_SORT_H
#define CH_2_1_INSERTION_SORT_H

#include "Base_sort.h"

template<typename Comparable>
class Insertion_sort : public Base_sort<Comparable> {
public:
    static const std::string tag;

    void sort(std::vector<Comparable> &a) final {
        int n = static_cast<int>(a.size());
        for (int i = 1; i < n; i++) {
            for (int j = i; j > 0 && Base_sort<Comparable>::less(a[j], a[j - 1]); j--) {
                Base_sort<Comparable>::exch(a, j, j - 1);
            }
        }
    }
};

template<typename Comparable>
const std::string Insertion_sort<Comparable>::tag{"insertion sort"};

#endif //CH_2_1_INSERTION_SORT_H
