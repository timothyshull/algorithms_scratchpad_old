// see list.cpp

//#include <cstdlib>
//#include "list.h"
//
//Link freelist;
//
//void construct(int N)
//{
//    freelist = new node[N + 1];
//    for (int i = 0; i < N; ++i) {
//        freelist[i].next = &freelist[i + 1];
//    }
//    freelist[N].next = 0;
//}
//
//Link newNode(int i)
//{
//    Link x = remove(freelist);
//    x->item = i;
//    x->next = x;
//    return x;
//}
//
//void deleteNode(Link x) { insert(freelist, x); }
//
//void insert(Link x, Link t)
//{
//    t->next = x->next;
//    x->next = t;
//}
//
//Link remove(Link x)
//{
//    Link t = x->next;
//    x->next = t->next;
//    return t;
//}
//
//Link next(Link x) { return x->next; }
//
//Item item(Link x) { return x->item; }
//
