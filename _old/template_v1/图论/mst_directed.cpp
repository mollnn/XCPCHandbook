// MST for Directed Graph
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 100 + 5;
const int M = 10000 + 5;
const ll INF = 0x3f3f3f3f;

int n, m, r;

struct edge {int u, v, w;} e[M];

int fa[N], id[N], top[N], minw[N];

ll get_ans (int n, int m) {
    ll ans = 0;
    while (true) {
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            id[i] = top[i] = 0; minw[i] = INF;
        }
        for (int i = 0; i < m; ++i) {
            if (e[i].u != e[i].v && e[i].w < minw[e[i].v]) {
                fa[e[i].v] = e[i].u;
                minw[e[i].v] = e[i].w;
            }
        }
        minw[r] = 0;
        for (int i = 1; i <= n; ++i) {
            if (minw[i] == INF) return -1;
            ans += minw[i];
            int u = i;
            while (u != r && top[u] != i && !id[u]) {
                top[u] = i;
                u = fa[u];
            }
            if (u != r && !id[u]) {
                id[u] = ++cnt;
                for (int v = fa[u]; v != u; v = fa[v]) id[v] = cnt;
            }
        }
        if (cnt == 0) return ans;
        for (int i = 1; i <= n; ++i) {
            if (!id[i]) id[i] = ++cnt;
        }
        for (int i = 0; i < m; ++i) {
            int prew = minw[e[i].v];
            e[i].u = id[e[i].u];
            e[i].v = id[e[i].v];
            if (e[i].u != e[i].v) {
                e[i].w -= prew;
            }
        }
        n = cnt; r = id[r];
    }
}

int main () {
    cin >> n >> m >> r;
    for (int i = 0; i < m; ++i) {
        static int u, v, w;
        cin >> u >> v >> w;
        e[i] = (edge) {u, v, w};
    }
    cout << get_ans (n, m) << endl;
}
