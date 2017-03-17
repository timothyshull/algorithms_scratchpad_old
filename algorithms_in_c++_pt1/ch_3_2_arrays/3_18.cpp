// faster
#include <iostream>
#include <set>

static const int range = 1000;

int random_in_range() {
    return rand() % range;
}

int count_until_repeat() {
    int count = 0;

    std::set<int> values;
    while (values.size() != range) {
        values.insert(random_in_range());
        count++;
    }
    return count;
}

int main() {
    for (int i = 0; i < range; i++) {
        std::cout << "The number of random values generated before each value was generated was " << i << " was: " << count_until_repeat() << "\n";
    }

    return 0;
}

// slower
//#include <iostream>
//
//static const int range = 1000;
//int counts[range];
//
//int random_in_range() {
//    return rand() % range;
//}
//
//int count_until_repeat() {
//    int count = 0;
//    for (int i = 0; i < range; i++) {
//        counts[i] = 0;
//    }
//
//    bool all_set = false;
//    while (!all_set) {
//        counts[random_in_range()]++;
//        all_set = true;
//        for (int i = 0; i < range; i++) {
//            if (!counts[i]) {
//                all_set = false;
//            }
//        }
//        count++;
//    }
//    return count;
//}
//
//int main() {
//    for (int i = 0; i < range; i++) {
//        std::cout << "The number of random values generated before each value was generated was " << i << " was: " << count_until_repeat() << "\n";
//    }
//
//    return 0;
//}