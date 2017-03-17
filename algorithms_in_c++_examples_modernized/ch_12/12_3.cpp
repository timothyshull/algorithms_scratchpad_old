#include <iostream>
#include <stdlib.h>
#include "Item.cxx"
#include "ST.cxx"

int main(int argc, char* argv[])
{
    int N, maxN = atoi(argv[1]), sw = atoi(argv[2]);
    ST <Item, Key> st(maxN);
    for (N = 0; N < maxN; ++N) {
        Item v;
        if (sw) { v.rand(); } else if (!v.scan()) { break; }
        if (!(st.search(v.key())).null()) { continue; }
        st.insert(v);
    }
    st.show(std::cout);
    std::cout << "\n";
    std::cout << N << " keys" << "\n";
    std::cout << st.count() << " distinct keys" << "\n";
}

