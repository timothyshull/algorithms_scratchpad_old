int phiR(int v)
{
    if (mark[v] == valid) { return phi[v]; }
    phi[v] = phiR(ST(v)) - st[v]->costRto(v);
    mark[v] = valid;
    return phi[v];
}

