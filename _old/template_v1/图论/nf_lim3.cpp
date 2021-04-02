#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAX_NODE = 1000005;
namespace Network {
ll tInfinity = 1e+15;
struct edge {
    ll p, o;
    ll c, id;
};
ll s, t;
ll ans, tans;
ll dis[MAX_NODE];
vector<edge> g[MAX_NODE];
void make_edge(ll p, ll q, ll c, ll id) {
    ll sz1 = g[p].size(), sz2 = g[q].size();
    edge tmp;
    tmp.p = q;
    tmp.c = c;
    tmp.o = sz2;
    tmp.id = id;
    g[p].push_back(tmp);
    tmp.p = p;
    tmp.c = 0;
    tmp.o = sz1;
    tmp.id = -id;
    g[q].push_back(tmp);
}
void reset_graph(ll maxnode) {
    for (ll i = 0; i <= maxnode; i++) g[i].clear();
}
ll dinic_bfs() {
    queue<ll> q;
    q.push(s);
    memset(dis, 0xff, sizeof dis);
    dis[s] = 1;
    while (q.size()) {
        ll p = q.front();
        q.pop();
        for (ll i = 0; i < g[p].size(); i++)
            if (g[p][i].c > 0 && dis[g[p][i].p] < 0)
                q.push(g[p][i].p), dis[g[p][i].p] = dis[p] + 1;
    }
    return dis[t] > 0;
}
ll dinic_dfs(ll p, ll lim) {
    ll flow = 0;
    if (p == t)
        return lim;
    for (ll i = 0; i < g[p].size(); i++) {
        if (g[p][i].c > 0 && dis[g[p][i].p] == dis[p] + 1) {
            ll tmp = dinic_dfs(g[p][i].p, min(lim, g[p][i].c));
            if (tmp > 0) {
                g[p][i].c -= tmp;
                g[g[p][i].p][g[p][i].o].c += tmp;
                flow += tmp;
                lim -= tmp;
            }
        }
    }
    return flow;
}
ll solve(ll src, ll tar) {
    s = src;
    t = tar;
    ans = 0;
    tans = 0;
    while (dinic_bfs()) {
        while (tans = dinic_dfs(s, tInfinity)) {
            ans += tans;
        }
    }
    return ans;
}
};  // namespace Network

ll n, m, s, t, ps, pt, low, upp, E[MAX_NODE][5];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> ps >> pt;
    ll sum = 0, ans = 0;
    for (ll i = 1; i <= m; i++) {
        cin >> s >> t >> low >> upp;
        E[i][0] = s;
        E[i][1] = t;
        E[i][2] = low;
        E[i][3] = upp;
        Network::make_edge(n + 1, t, low, i);
        Network::make_edge(s, n + 2, low, i);
        Network::make_edge(s, t, upp - low, i);
        sum += low;
    }
    Network::make_edge(pt, ps, 1e+15, 0);
    if (sum == (Network::solve(n + 1, n + 2))) {
        for (int i = 0; i < Network::g[ps].size(); i++)
            if (Network::g[ps][i].id == 0)
                ans = Network::g[ps][i].c, Network::g[ps][i].c = 0;
        for (int i = 0; i < Network::g[pt].size(); i++)
            if (Network::g[pt][i].id == 0)
                Network::g[pt][i].c = 0;
        ans -= Network::solve(pt, ps);
        cout << ans << endl;
    } else {
        cout << "please go home to sleep" << endl;
    }
    return 0;
}
