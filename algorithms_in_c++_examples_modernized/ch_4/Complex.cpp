#include <iostream>
#include "Complex.h"

Complex::Complex(float x, float y) : re_{x}, im_{y} {}

inline float Complex::re() const { return re_; }

inline float Complex::im() const { return im_; }

Complex& Complex::operator*=(const Complex& rhs)
{
    float t = re_;
    re_ = re_ * rhs.re_ - im_ * rhs.im_;
    im_ = t * rhs.im_ + im_ * rhs.re_;
    return *this;
}

std::ostream& operator<<(std::ostream& t, const Complex& c)
{
    t << c.re() << " " << c.im();
    return t;
}
