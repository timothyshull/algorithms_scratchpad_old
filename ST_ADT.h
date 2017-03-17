#ifndef ALGS_CPP_ST_ADT_H
#define ALGS_CPP_ST_ADT_H

#include <iosfwd>

template<typename Item, typename Key>
class ST_ADT {
private:
// implementation specific
public:
    ST_ADT();

    ST_ADT(int);

    int count();

    Item search(Key);

    void insert(Item);

    void remove(Item);

    Item select(int);

    void show(std::ostream &);
};

#endif //ALGS_CPP_ST_ADT_H
