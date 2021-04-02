// DU's Sieve Algorithm
// O(n^0.67) to solve prefix sum of mu or phi
// in the demo below, n <= 2^31-1
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
map<int, ll> sphi, smu;
bool notprime[5000001];
int t, n, prime[5000001], top = 0;
ll phi[5000001], mu[5000001];

inline void pre() {
    phi[1] = 1; mu[1] = 1;
    for (register int i = 2; i <= 5000000; ++i) {
        if (!notprime[i]) prime[++top] = i, phi[i] = i - 1, mu[i] = -1;
        for (register int j = 1; j <= top; ++j) {
            if (i * prime[j] > 5000000) break;
            notprime[i * prime[j]] = 1;
            if (!(i % prime[j])) {
                phi[i * prime[j]] = phi[i] * prime[j];
                mu[i * prime[j]] = 0;
                break;
            } else {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
                mu[i * prime[j]] = -1 * mu[i];
            }
        }
    }
    for (register int i = 2; i <= 5000000; ++i) phi[i] += phi[i - 1], mu[i] += mu[i - 1];
}

ll calcphi(int n) {
    if (n <= 5000000) return phi[n];
    if (sphi[n]) return sphi[n];
    ll rt = (ll)n * (ll)(n + 1) / 2;
    for (register unsigned int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        rt -= (r - l + 1) * calcphi(n / l);
    }
    return sphi[n] = rt;
}

ll calcmu(int n) {
    if (n <= 5000000) return mu[n];
    if (smu[n]) return smu[n];
    ll rt = 1;
    for (register unsigned int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        rt -= (r - l + 1) * calcmu(n / l);
    }
    return smu[n] = rt;
}

int main() {
    cin>>t; pre();
    while (t--) {
        cin>>n;
        printf("%lld %lld\n", calcphi(n), calcmu(n));
    }
    return 0;
}
