#ifndef CH_4_0_ABSTRACT_DATA_TYPES_POINT_H
#define CH_4_0_ABSTRACT_DATA_TYPES_POINT_H

#include <cmath>
#include <cstdlib>

class POINT {
private:
    float x, y;
public:
    POINT() {
        x = (float) (1.0 * rand() / RAND_MAX);
        y = (float) (1.0 * rand() / RAND_MAX);
    }

    float distance(POINT a) {
        float dx = x - a.x, dy = y - a.y;
        return (float) (sqrt(dx * dx + dy * dy));
    }
};

#endif //CH_4_0_ABSTRACT_DATA_TYPES_POINT_H