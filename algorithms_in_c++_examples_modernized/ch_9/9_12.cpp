template<class Index>
class PQ {
private:
    int N;
    Index* pq;
    int* qp;

    void exch(Index i, Index j)
    {
        int t;
        t = qp[i];
        qp[i] = qp[j];
        qp[j] = t;
        pq[qp[i]] = i;
        pq[qp[j]] = j;
    }

    void fixUp(Index a[], int k);

    void fixDown(Index a[], int k, int N);

public:
    PQ(int maxN)
    {
        pq = new Index[maxN + 1];
        qp = new int[maxN + 1];
        N = 0;
    }

    int empty() const { return N == 0; }

    void insert(Index v)
    {
        ++pq[N] = v;
        qp[v] = N;
        fixUp(pq, N);
    }

    Index getmax()
    {
        exch(pq[1], pq[N]);
        fixDown(pq, 1, N - 1);
        return pq[N--];
    }

    void change(Index k)
    {
        fixUp(pq, qp[k]);
        fixDown(pq, qp[k], N);
    }
};

