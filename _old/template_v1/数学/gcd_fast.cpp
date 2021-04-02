// Fast GCD (n,v)
// presolve: O(v)
// query: O(1)
// 5 seconds used when n=5000 (full query) and v=1e+6
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int maxn = 5000, v = 1000000, radio = 1000;
int a[maxn + 10], b[maxn + 10], n, ans;
int np[v + 10], prime[v + 10], cnt;
int k[v + 10][3];
int _gcd[radio + 10][radio + 10];
inline int gcd(int a, int b) {
    int g = 1;
    for(int tmp, i = 0; i < 3; i++) {
        if(k[a][i] > radio) {
            if(b % k[a][i] == 0) tmp = k[a][i];
            else tmp = 1;
        }
        else tmp = _gcd[k[a][i]][b % k[a][i]];
        b /= tmp;
        g *= tmp;
    }
    return g;
}
int main() {
    // Presolve
    k[1][0] = k[1][1] = k[1][2] = 1;
    np[1] = 1;
    for(int i = 2; i <= v; i++) {
        if(!np[i]) prime[++cnt] = i, k[i][2] = i, k[i][1] = k[i][0] = 1;
        for(int j = 1; prime[j] * i <= v; j++) {
            np[i * prime[j]] = 1;
            int *tmp = k[i * prime[j]];
            tmp[0] = k[i][0] * prime[j];
            tmp[1] = k[i][1];
            tmp[2] = k[i][2];
            if(tmp[1] < tmp[0]) swap(tmp[1], tmp[0]);
            if(tmp[2] < tmp[1]) swap(tmp[2], tmp[1]);
            if(i % prime[j] == 0) break;
        }
    }
    for(int i = 1; i <= radio; i++) _gcd[i][0] = _gcd[0][i] = i;
    for(int _max = 1; _max <= radio; _max++)
        for(int i = 1; i <= _max; i++)
            _gcd[i][_max] = _gcd[_max][i] = _gcd[_max % i][i];
    // Test A
    // for(int i = 1; i <= 10; i++)
        // for(int j = 1; j <= 10; j++) printf("gcd(%d, %d) = %d\n", i, j, _gcd[i][j]);
    // Test B
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", a + i);
    for(int i = 1; i <= n; i++) scanf("%d", b + i);
    for(int i = 1; i <= n; i++) {
        int now = 1, ans = 0;
        for(int j = 1; j <= n; j++) {
            now = 1ll * now * i % mod;
            ans = (ans + 1ll * gcd(a[i], b[j]) * now) % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}
