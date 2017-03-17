#include <cmath>

template<typename Item, typename std::enable_if<std::is_floating_point<Item>::value>::type>
bool operator==(Item &rhs, Item &lhs) {
    return fabs(rhs - lhs) / (fabs(rhs) < fabs(lhs) ? fabs(lhs) : fabs(rhs)) < pow(10, -6);
}