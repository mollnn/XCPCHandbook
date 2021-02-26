struct Graph
{
    int n, m;
    vector<vector<pair<int, int>>> g;
    void build(int n_, int m_)
    {
        n = n_;
        m = m_;
        g.resize(n + 2);
    }

    void make(int p, int q, int w)
    {
        g[p].push_back({q, w});
        g[q].push_back({p, w});
    }

    int dijkstra(int s0, int t0)
    {
        struct Node
        {
            int d, p;
            bool operator<(const Node &rhs) const
            {
                return d > rhs.d;
            }
        };

        priority_queue<Node> que;
        que.push({0, s0});
        vector<int> d(n + 2, 1e18);
        vector<int> v(n + 2, 0);
        d[s0] = 0;

        while (que.size())
        {
            auto [dis, p] = que.top();
            que.pop();
            if (v[p])
                continue;
            v[p] = 1;
            for (auto [q, w] : g[p])
            {
                if (d[q] > d[p] + w)
                {
                    d[q] = d[p] + w;
                    que.push({d[q], q});
                }
            }
        }

        return d[t0];
    }
};