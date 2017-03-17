#include <stdlib.h>
#include <iostream>

static int maxKey = 1000;

using Key = int;

class Item {
private:
    Key keyval;
    float info;
public:
    Item() { keyval = maxKey; }

    Key key() { return keyval; }

    int null() { return keyval == maxKey; }

    void rand()
    {
        keyval = 1000 * ::rand() / RAND_MAX;
        info = 1.0 * ::rand() / RAND_MAX;
    }

    int scan(istream& is = std::cin) { return (is >> keyval >> info) != 0; }

    void show(ostream& os = std::cout) { os << keyval << " " << info << "\n"; }
};

ostream& operator<<(ostream& os, Item& x)
{
    x.show(os);
    return os;
}

