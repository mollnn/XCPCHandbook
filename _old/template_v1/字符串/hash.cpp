#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll modulo = 1000000007;
const ll base = 131;

string str;
ll h[1000005];

ll qpow(ll p,ll q) {
    ll r = 1;
    for(; q; p*=p, p%=modulo, q>>=1) if(q&1) r*=p, r%=modulo;
    return r;
}

void prehash() {
    for(int i=0;i<=str.length();i++) h[i]=0;
    h[0] = str[0];
    for(int i=1;i<str.length();i++)
        h[i] = (str[i] + h[i-1]*base) % modulo;
}

ll gethash(int l,int r) { // Warning: index = 0..n-1
    if(l==0) return h[r];
    return ((h[r] - h[l-1]*qpow(base,r-l+1))%modulo + modulo)%modulo;
}

int main() {
    ios::sync_with_stdio(false);
    while(cin>>str) {
        prehash();
        int n = str.length();
        for(int i=1;i<=n;i++)
            if(gethash(0,i-1) == gethash(n-i,n-1))
                cout<<i<<" ";
        cout<<endl;
    }
}
