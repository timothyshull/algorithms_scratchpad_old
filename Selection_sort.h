#ifndef CH_2_1_SELECTION_SORT_H
#define CH_2_1_SELECTION_SORT_H

#include "Base_sort.h"

template<typename Comparable>
class Selection_sort : public Base_sort<Comparable> {
public:
    static const std::string tag;

    void sort(std::vector<Comparable> &a) final {
        int n = static_cast<int>(a.size());
        for (int i = 0; i < n; i++) {
            int min = i;
            for (int j = i + 1; j < n; j++) {
                if (Base_sort<Comparable>::less(a[j], a[min])) {
                    min = j;
                }
            }
            Base_sort<Comparable>::exch(a, i, min);
        }
    }
};

template<typename Comparable>
const std::string Selection_sort<Comparable>::tag{"selection sort"};

#endif //CH_2_1_SELECTION_SORT_H
