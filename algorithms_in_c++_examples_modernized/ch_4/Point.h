#ifndef POINT_H
#define POINT_H

#include <random>

namespace __impl {
    using std::random_device;
    using std::default_random_engine;
    using std::uniform_real_distribution;

    static random_device rd;

    static default_random_engine gen(rd());

    static uniform_real_distribution<float> uniform_dist(0, 1);

    float rand_float()
    {
        return uniform_dist(gen);
    }
}

class Point {
private:
    float x;
    float y;
public:
    Point() : x{__impl::rand_float()}, y{__impl::rand_float()} {}

    float distance(Point& a)
    {
        float dx = x - a.x;
        float dy = y - a.y;
        return static_cast<float>(sqrt(dx * dx + dy * dy));
    }
};

#endif //POINT_H
