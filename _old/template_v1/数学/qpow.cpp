ll qpow(ll p,ll q) {
    ll r = 1;
    for(; q; p*=p, p%=modulo, q>>=1) if(q&1) r*=p, r%=modulo;
    return r;
}
