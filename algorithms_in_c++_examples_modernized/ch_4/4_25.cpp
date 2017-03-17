template<class Number>
class POLY {
private:
    int n;
    Number* a;
public:
    POLY<Number>(Number c, int N)
    {
        a = new Number[N + 1];
        n = N + 1;
        a[N] = c;
        for (int i = 0; i < N; ++i) { a[i] = 0; }
    }

    float eval(float x) const
    {
        double t = 0.0;
        for (int i = n - 1; i >= 0; i--) {
            t = t * x + a[i];
        }
        return t;
    }

    friend POLY operator+(POLY& p, POLY& q)
    {
        POLY t(0, p.n > q.n ? p.n - 1 : q.n - 1);
        for (int i = 0; i < p.n; ++i) {
            t.a[i] += p.a[i];
        }
        for (int j = 0; j < q.n; ++j) {
            t.a[j] += q.a[j];
        }
        return t;
    }

    friend POLY operator*(POLY& p, POLY& q)
    {
        POLY t(0, (p.n - 1) + (q.n - 1));
        for (int i = 0; i < p.n; ++i) {
            for (int j = 0; j < q.n; ++j) {
                t.a[i + j] += p.a[i] * q.a[j];
            }
        }
        return t;
    }
};


