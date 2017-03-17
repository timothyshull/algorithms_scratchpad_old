enum class Suit {
    Hearts,
    Clubs,
    Spades,
    Diamonds
};

enum class Face_value {
    Ace,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};

struct Playing_card {
    Suit suit;
    Face_value value;
};