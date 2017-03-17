#ifndef ALGS_CPP_POINT_H
#define ALGS_CPP_POINT_H

template<typename T>
class point {
    T x, y;
public:
    point(T a, T b) : x{a}, y{b} { }

    inline T get_x() { return x; }
    inline T get_y() { return y; }
};

#endif //ALGS_CPP_POINT_H
