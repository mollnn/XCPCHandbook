#include <bits/stdc++.h>
using namespace std;
const int MAX_NODE = 1000005;
namespace Network {
int tInfinity = 1e+9;
struct edge {
    int p, o;
    int c, id;
};
int s, t;
int ans, tans;
int dis[MAX_NODE];
vector<edge> g[MAX_NODE];
void make_edge(int p, int q, int c, int id) {
    int sz1 = g[p].size(), sz2 = g[q].size();
    edge tmp;
    tmp.p = q;
    tmp.c = c;
    tmp.o = sz2;
    tmp.id = id;
    g[p].push_back(tmp);
    tmp.p = p;
    tmp.c = 0;
    tmp.o = sz1;
    tmp.id = 0;
    g[q].push_back(tmp);
}
void reset_graph(int maxnode) {
    for (int i = 0; i <= maxnode; i++) g[i].clear();
}
int dinic_bfs() {
    queue<int> q;
    q.push(s);
    memset(dis, 0xff, sizeof dis);
    dis[s] = 1;
    while (q.size()) {
        int p = q.front();
        q.pop();
        for (int i = 0; i < g[p].size(); i++)
            if (g[p][i].c > 0 && dis[g[p][i].p] < 0)
                q.push(g[p][i].p), dis[g[p][i].p] = dis[p] + 1;
    }
    return dis[t] > 0;
}
int dinic_dfs(int p, int lim) {
    int flow = 0;
    if (p == t)
        return lim;
    for (int i = 0; i < g[p].size(); i++) {
        if (g[p][i].c > 0 && dis[g[p][i].p] == dis[p] + 1) {
            int tmp = dinic_dfs(g[p][i].p, min(lim, g[p][i].c));
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
int solve(int src, int tar) {
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

int n, m, s, t, low, upp, E[MAX_NODE][5];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    int sum = 0;
    for (int i = 1; i <= m; i++) {
        cin >> s >> t >> low >> upp;
        E[i][0] = s;
        E[i][1] = t;
        E[i][2] = low;
        E[i][3] = upp;
        Network::make_edge(n + 1, t, low, 0);
        Network::make_edge(s, n + 2, low, 0);
        Network::make_edge(s, t, upp - low, i);
        sum += low;
    }
    if (sum == Network::solve(n + 1, n + 2)) {
        cout << "YES" << endl;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < Network::g[i].size(); j++) E[Network::g[i][j].id][4] = Network::g[i][j].c;
        }
        for (int i = 1; i <= m; i++) {
            cout << E[i][3] - E[i][4] << endl;
        }
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
