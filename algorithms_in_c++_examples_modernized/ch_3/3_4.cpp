#include <cmath>
#include "Point.h"

float distance(Point& a, Point& b)
{
    float dx{a.x - b.x};
    float dy{a.y - b.y};
    return std::sqrtf(dx * dx + dy * dy);
}

