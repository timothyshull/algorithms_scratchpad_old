#include <iostream>
#include "ST_ADT.h"
#include "Item_ADT.h"

int main(int argc, char *argv[]) {
    int N;
    int maxN = atoi(argv[1]);
    int sw = atoi(argv[2]);

    ST_ADT<Item, Key> st(maxN);
    for (N = 0; N < maxN; N++) {
        Item v;
        if (sw) v.rand();
        else if (!v.scan()) break;
        if (!(st.search(v.key())).null()) continue;
        st.insert(v);
    }

    st.show(std::cout);
    std::cout << std::endl;
    std::cout << st.count() << " distinct keys" << std::endl;
    return 0;
}