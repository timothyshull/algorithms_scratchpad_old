#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
private:
    float re_;
    float im_;
public:
    Complex(float x, float y);

    inline float re() const;

    inline float im() const;

    Complex& operator*=(const Complex& rhs);
};

std::ostream& operator<<(std::ostream& t, const Complex& c);

#endif //COMPLEX_H
