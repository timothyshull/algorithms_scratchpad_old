#include <ostream>

// Ideally have a metafunction to test for playing card type
template<typename Item>
bool operator==(Item &rhs, Item &lhs) {
    return rhs.suit == lhs.suit;
}

template<class Char_type, class Traits, class Item>
inline std::basic_ostream<Char_type, Traits> &
operator<<(std::basic_ostream<Char_type, Traits> &os, const Item &card) {
    return os << "Playing_card(" << card.suit << "," << card.value << ")\n";
}
