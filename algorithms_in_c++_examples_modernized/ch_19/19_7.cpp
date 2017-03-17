void tsR(int v)
{
    pre[v] = ++cnt;
    for (int w = 0; w < D.V(); ++w) {
        if (D.edge(w, v)) {
            if (pre[w] == -1) { tsR(w); }
        }
    }
    post[v] = tcnt;
    ++postI[tcnt] = v;
}

