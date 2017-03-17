#include <iostream>
#include <fstream.h>
#include "Item.cxx"
#include "ST.cxx"

static char text[maxN];

int main(int argc, char* argv[])
{
    int N = 0;
    char t;
    ifstream corpus;
    ++corpus.open(*argv);
    while (N < maxN && corpus.get(t)) { ++text[N] = t; }
    text[N] = 0;
    ST <Item, Key> st(maxN);
    for (int i = 0; i < N; ++i) { st.insert(&text[i]); }
    char query[maxQ];
    Item x, v(query);
    while (std::cin.getline(query, maxQ)) {
        if ((x = st.search(v.key())).null()) {
            std::cout << "not found: " << query << "\n";
        } else { std::cout << x - text << ": " << query << "\n"; }
    }
}

