#include <vector>
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>

template<typename Iterator_type>
void iterator_selection_sort(Iterator_type first, Iterator_type last)
{
    Iterator_type lm = last;
    for (--lm; first != lm; ++first) {
        Iterator_type i = first;
        Iterator_type min = first;
        while (++i != last) {
            if (*i < *min) {
                min = i;
            }
        }
        i = min;
        if (i != first) {
            std::swap(*first, *i);
        }
    }
}

template<typename T>
void selection_sort(std::vector<T>& data)
{
    auto n{data.size()};
    for (int i = 0; i < n; ++i) {
        int min = i;
        for (int j = i + 1; j < n; ++j) {
            if (std::less<T>{}(data[j], data[min])) {
                min = j;
            }
        }
        std::swap(data[i], data[min]);
    }
}

// can add back comparator here
template<class Iterator_type>
void iterator_insertion_sort(Iterator_type first, Iterator_type last)
{
    using value_type = typename std::iterator_traits<Iterator_type>::value_type;
    if (first != last) {
        Iterator_type i{first};
        for (++i; i != last; ++i) {
            Iterator_type j{i};
            value_type t{std::move(*j)};
            for (Iterator_type k = i; k != first && t < *--k; --j) {
                *j = std::move(*k);
            }
            *j = std::move(t);
        }
    }
}

int main()
{
    std::array<int, 10> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};

    // sort using the default operator<
    iterator_selection_sort(s.begin(), s.end());
    for (auto a : s) {
        std::cout << a << " ";
    }
    std::cout << '\n';

    std::vector<int> v = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};

    selection_sort(v);
    for (auto a : v) {
        std::cout << a << " ";
    }
    std::cout << '\n';

    return 0;
}