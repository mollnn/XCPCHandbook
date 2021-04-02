#include <bits/stdc++.h>
using namespace std;
namespace flow {

const int maxn = 200005;
const int inf = 1e+9;

int dis[maxn], ans, cnt = 1, s, t, pre[maxn * 10], nxt[maxn * 10], h[maxn], v[maxn * 10];
std::queue<int> q;
void make(int x, int y, int z) {
    pre[++cnt] = y, nxt[cnt] = h[x], h[x] = cnt, v[cnt] = z;
    pre[++cnt] = x, nxt[cnt] = h[y], h[y] = cnt;
}
bool bfs() {
    memset(dis, 0, sizeof dis);
    q.push(s), dis[s] = 1;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = h[x]; i; i = nxt[i])
            if (!dis[pre[i]] && v[i])
                dis[pre[i]] = dis[x] + 1, q.push(pre[i]);
    }
    return dis[t];
}
int dfs(int x, int flow) {
    if (x == t || !flow)
        return flow;
    int f = flow;
    for (int i = h[x]; i; i = nxt[i])
        if (v[i] && dis[pre[i]] > dis[x]) {
            int y = dfs(pre[i], min(v[i], f));
            f -= y, v[i] -= y, v[i ^ 1] += y;
            if (!f)
                return flow;
        }
    if (f == flow)
        dis[x] = -1;
    return flow - f;
}
int solve(int _s,int _t) {
    s=_s;
    t=_t;
    ans = 0;
    for (; bfs(); ans += dfs(s, inf));
    return ans;
}
}

int n, m, s, t, t1, t2, t3;

int main() {
    cin>>n>>m>>s>>t;
    for(int i=1;i<=m;i++) {
        cin>>t1>>t2>>t3;
        flow::make(t1,t2,t3);
    }
    cout<<flow::solve(s,t);
}
