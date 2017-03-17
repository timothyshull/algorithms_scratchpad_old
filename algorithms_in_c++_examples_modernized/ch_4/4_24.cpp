template<class Number>
class POLY {
private:
    // Implementation-dependent code
public:
    POLY<Number>(Number, int);

    float eval(float) const;

    friend POLY operator+(POLY&, POLY&);

    friend POLY operator*(POLY&, POLY&);
};

