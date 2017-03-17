#ifndef CH_2_1_SHELL_SORT_H
#define CH_2_1_SHELL_SORT_H

#include "Base_sort.h"

template<typename Comparable>
class Shell_sort : public Base_sort<Comparable> {
public:
    static const std::string tag;

    void sort(std::vector<Comparable> &a) final {
        int n = static_cast<int>(a.size());
        int h = 1;

        while (h < n / 3) {
            h = 3 * h + 1;
        }

        while (h >= 1) {
            for (int i = h; i < n; i++) {
                for (int j = i; j >= h && Base_sort<Comparable>::less(a[j], a[j - h]); j -= h) {
                    Base_sort<Comparable>::exch(a, j, j - h);
                }
                h = h / 3;
            }
        }
    }
};

template<typename Comparable>
const std::string Shell_sort<Comparable>::tag{"shell sort"};

#endif //CH_2_1_SHELL_SORT_H
