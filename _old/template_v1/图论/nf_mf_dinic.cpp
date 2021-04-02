template <class T> class Graph_Maxflow_Dinic {
public:
	T tInfinity;
	struct edge {
		int p, o;
		T c;
	};
	int s, t;
	T ans, tans;
	T dis[MAX_NODE];
	vector <edge> g[MAX_NODE];
	Graph_Maxflow_Dinic() {
		tInfinity = 1e+9;
	}
	void make_edge(int p, int q, T c) {
		int sz1 = g[p].size(), sz2 = g[q].size();
		edge tmp;
		tmp.p = q;
		tmp.c = c;
		tmp.o = sz2;
		g[p].push_back(tmp);
		tmp.p = p;
		tmp.c = 0;
		tmp.o = sz1;
		g[q].push_back(tmp);
	}
	void reset_graph(int maxnode) {
		for (int i = 0; i <= maxnode; i++)
			g[i].clear();
	}
	int dinic_bfs() {
		queue<int> q;
		q.push(s);
		memset(dis, 0xff, sizeof dis);
		dis[s] = 1;
		while (q.size()) {
			int p = q.front(); q.pop();
			for (int i = 0; i < g[p].size(); i++)
				if (g[p][i].c > 0 && dis[g[p][i].p] < 0)
					q.push(g[p][i].p),
					dis[g[p][i].p] = dis[p] + 1;
		}
		return dis[t] > 0;
	}
	T dinic_dfs(int p, T lim) {
		T flow = 0;
		if (p == t) return lim;
		for (int i = 0; i < g[p].size(); i++) {
			if (g[p][i].c > 0 && dis[g[p][i].p] == dis[p] + 1) {
				T tmp = dinic_dfs(g[p][i].p, min(lim, g[p][i].c));
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
	T solve(int src, int tar) {
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
};
