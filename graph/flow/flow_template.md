## 网络流模板 v4

【使用指南】

1. 修改合适的 N 和 M
2. 创建对象 `flowsolution::MaxflowSolution flow;` 或 `flowsolution::CostflowSolution flow;`
3. 调用 `make` 成员函数建边
4. 调用 `solve` 成员函数计算结果

``` cpp
#ifndef __FLOW_HPP__
#define __FLOW_HPP__

#include <bits/stdc++.h>
using namespace std;
#define int long long

namespace flowsolution
{
    const int N = 100005;
    const int M = 1000005;
    const int inf = 1e+12;

    struct MaxflowSolution
    {
        int *dis, ans, cnt = 1, s, t, *pre, *next, *head, *val;

        MaxflowSolution()
        {
            cnt = 1;
            dis = new int[N];
            pre = new int[M];
            next = new int[M];
            head = new int[N];
            val = new int[M];
            fill(dis, dis + N, 0);
            fill(pre, pre + M, 0);
            fill(next, next + M, 0);
            fill(head, head + N, 0);
            fill(val, val + M, 0);
        }

        ~MaxflowSolution()
        {
            delete[] dis;
            delete[] pre;
            delete[] next;
            delete[] head;
            delete[] val;
        }

        std::queue<int> q;
        void make(int x, int y, int z)
        {
            pre[++cnt] = y, next[cnt] = head[x], head[x] = cnt, val[cnt] = z;
            pre[++cnt] = x, next[cnt] = head[y], head[y] = cnt;
        }

        bool bfs()
        {
            fill(dis, dis + N, 0);
            q.push(s), dis[s] = 1;
            while (!q.empty())
            {
                int x = q.front();
                q.pop();
                for (int i = head[x]; i; i = next[i])
                    if (!dis[pre[i]] && val[i])
                        dis[pre[i]] = dis[x] + 1, q.push(pre[i]);
            }
            return dis[t];
        }

        int dfs(int x, int flow)
        {
            if (x == t || !flow)
                return flow;
            int f = flow;
            for (int i = head[x]; i; i = next[i])
                if (val[i] && dis[pre[i]] > dis[x])
                {
                    int y = dfs(pre[i], min(val[i], f));
                    f -= y, val[i] -= y, val[i ^ 1] += y;
                    if (!f)
                        return flow;
                }
            if (f == flow)
                dis[x] = -1;
            return flow - f;
        }

        int solve(int _s, int _t)
        {
            s = _s;
            t = _t;
            ans = 0;
            for (; bfs(); ans += dfs(s, inf))
                ;
            return ans;
        }
    };

    struct CostflowSolution
    {
        struct Edge
        {
            int p = 0, c = 0, w = 0, next = -1;
        } * e;
        int s, t, tans, ans, cost, ind, *bus, qhead = 0, qtail = -1, *qu, *vis, *dist;

        CostflowSolution()
        {
            e = new Edge[M];
            qu = new int[M];
            bus = new int[N];
            vis = new int[N];
            dist = new int[N];
            fill(qu, qu + M, 0);
            fill(bus, bus + N, -1);
            fill(vis, vis + N, 0);
            fill(dist, dist + N, 0);
            ind = 0;
        }

        ~CostflowSolution()
        {
            delete[] e;
            delete[] qu;
            delete[] vis;
            delete[] dist;
        }

        void graph_link(int p, int q, int c, int w)
        {
            e[ind].p = q;
            e[ind].c = c;
            e[ind].w = w;
            e[ind].next = bus[p];
            bus[p] = ind;
            ++ind;
        }

        void make(int p, int q, int c, int w)
        {
            graph_link(p, q, c, w);
            graph_link(q, p, 0, -w);
        }

        int dinic_spfa()
        {
            qhead = 0;
            qtail = -1;
            fill(vis, vis + N, 0);
            fill(dist, dist + N, inf);
            vis[s] = 1;
            dist[s] = 0;
            qu[++qtail] = s;
            while (qtail >= qhead)
            {
                int p = qu[qhead++];
                vis[p] = 0;
                for (int i = bus[p]; i != -1; i = e[i].next)
                    if (dist[e[i].p] > dist[p] + e[i].w && e[i].c > 0)
                    {
                        dist[e[i].p] = dist[p] + e[i].w;
                        if (vis[e[i].p] == 0)
                            vis[e[i].p] = 1, qu[++qtail] = e[i].p;
                    }
            }
            return dist[t] < inf;
        }

        int dinic_dfs(int p, int lim)
        {
            if (p == t)
                return lim;
            vis[p] = 1;
            int ret = 0;
            for (int i = bus[p]; i != -1; i = e[i].next)
            {
                int q = e[i].p;
                if (e[i].c > 0 && dist[q] == dist[p] + e[i].w && vis[q] == 0)
                {
                    int res = dinic_dfs(q, min(lim, e[i].c));
                    cost += res * e[i].w;
                    e[i].c -= res;
                    e[i ^ 1].c += res;
                    ret += res;
                    lim -= res;
                    if (lim == 0)
                        break;
                }
            }
            return ret;
        }

        pair<int, int> solve(int _s, int _t)
        {
            s = _s;
            t = _t;
            ans = 0;
            cost = 0;
            while (dinic_spfa())
            {
                fill(vis, vis + N, 0);
                ans += dinic_dfs(s, inf);
            }
            return make_pair(ans, cost);
        }
    };
} // namespace flowsolution

#endif
```