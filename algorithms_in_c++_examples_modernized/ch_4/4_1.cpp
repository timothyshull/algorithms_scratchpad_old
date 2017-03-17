#include <cmath>
#include <cstdlib>

class POINT {
private:
    float x, y;
public:
    POINT()
    {
        x = 1.0 * rand() / RAND_MAX;
        y = 1.0 * rand() / RAND_MAX;
    }

    float distance(POINT a)
    {
        float dx = x - a.x, dy = y - a.y;
        return sqrt(dx * dx + dy * dy);
    }
};
