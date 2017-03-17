class Complex {
private:
    // Implementation-dependent code
public:
    Complex(float, float);

    float Re() const;

    float Im() const;

    Complex& operator*=(Complex&);
};

