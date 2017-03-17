enum value {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEEN,
    KING,
    ACE,
};

enum suit {
    HEARTS,
    CLUBS,
    SPADE,
    DIAMOND
};

struct card {
    suit _suit;
    value _value;
};