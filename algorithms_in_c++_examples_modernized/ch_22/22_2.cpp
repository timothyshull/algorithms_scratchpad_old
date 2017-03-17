class EDGE {
    int pv, pw, pcap, pflow;
public:
    EDGE(int v, int w, int cap) :
            pv(v), pw(w), pcap(cap), pflow(0) {}

    int v() const { return pv; }

    int w() const { return pw; }

    int cap() const { return pcap; }

    int flow() const { return pflow; }

    bool from(int v) const { return pv == v; }

    int other(int v) const { return from(v) ? pw : pv; }

    int capRto(int v) const { return from(v) ? pflow : pcap - pflow; }

    void addflowRto(int v, int d) { pflow += from(v) ? -d : d; }
};

