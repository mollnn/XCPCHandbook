class Graph_MincostMaxflow_Dinic { // 使用Dinic+SPFA求费用流（请手动修改类型:）
public:
	struct Item {
		int p, v, c;
	};
	Item item(int _p, int _v, int _c) {
		Item it;
		it.p = _p;
		it.v = _v;
		it.c = _c;
		return it;
	}
	vector <Item> g[MAX_NODE];
	int dis[MAX_NODE], d[MAX_NODE], vis[MAX_NODE], s, t, t4, costs = 0, tans, ans, inc[MAX_NODE], cnt = 0;
	queue <int> q;
	void reset_graph(int maxnode) {
		for (int i = 0; i <= maxnode; i++)
			g[i].clear();
	}
	void make_edge(int t1, int t2, int t3, int t4) {
		g[t1].push_back(item(t2, t4, t3)), g[t2].push_back(item(t1, -t4, 0));
	}
	int dinic_spfa() {
		memset(dis, 0xff, sizeof dis);
		memset(d, 0x3f, sizeof d);
		memset(vis, 0x00, sizeof vis);
		memset(inc, 0x00, sizeof inc);
		q.push(s); dis[s] = 0; d[s] = 0;
		while (!q.empty()) {
			int p = q.front(); q.pop(); vis[p] = 0; inc[p]++;
			for (int i = 0; i < g[p].size(); i++)
				if (d[g[p][i].p] > d[p] + g[p][i].v && g[p][i].c > 0) {
					dis[g[p][i].p] = p;
					d[g[p][i].p] = d[p] + g[p][i].v;
					if (vis[g[p][i].p] == 0) vis[g[p][i].p] = 1, q.push(g[p][i].p);
				}
		}
		return dis[t] > 0;
	}
	int dinic_dfs() {
		int p = t, a = 0x7fffffff;
		while (p - s) {
			for (int i = 0; i < g[dis[p]].size(); i++)
				if (g[dis[p]][i].p == p) {
					a = min(g[dis[p]][i].c, a);
					p = dis[p]; break;
				}
		}
		p = t;
		while (p - s) {
			for (int i = 0; i < g[p].size(); i++)
				if (g[p][i].p == dis[p])
					g[p][i].c += a;
			for (int i = 0; i < g[dis[p]].size(); i++)
				if (g[dis[p]][i].p == p)
					g[dis[p]][i].c -= a,
					costs += a * g[dis[p]][i].v;
			p = dis[p];
		}
		return a;
	}
	int solve(int src, int dest) { // 执行主计算任务，参数为源点和汇点
		s = src;
		t = dest;
		while (dinic_spfa()) ans += dinic_dfs();
		return costs;
	}
};
