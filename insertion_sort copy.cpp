#include <vector>
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>

template<typename T>
void insertion_sort(std::vector<T>& data)
{
    auto n{data.size()};
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0 && std::less<T>{}(data[j], data[j - 1]); --j) {
            std::swap(data[j], data[j - 1]);
        }
    }
}

// can add back comparator here
template<typename Iterator_type>
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
    iterator_insertion_sort(s.begin(), s.end());
    for (auto a : s) {
        std::cout << a << " ";
    }
    std::cout << '\n';

    std::vector<int> v = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};

    insertion_sort(v);
    for (auto a : v) {
        std::cout << a << " ";
    }
    std::cout << '\n';

    return 0;
}