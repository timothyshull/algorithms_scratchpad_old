#include <iostream>
#include "list_template.h"

int main() {
    ListElement<int> *e = new ListElement<int>({1, 2, 3, 4});
    e->traverseAndPrint();
    delete e;
    return 0;
}