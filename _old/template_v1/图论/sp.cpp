template <class T> class Graph_SP { // 解决单源最短路径问题
public:
	vector<pair<int, T> >G[MAX_NODE];
	int d[MAX_NODE], v[MAX_NODE]; // 距离表与访问标识表
	void make_edge(int t1, int t2, T t3) { // 造边（有向）
		G[t1].push_back(make_pair(t2, t3));
	}
	void reset_graph(int n) { // 用于清除图邻接表
		for (int i = 0; i <= n; i++)
			G[i].clear();
	}
	void reset_solver(int n) { // 对距离表与访问标识表的清除 如果改变了类型，该函数可能需要重写！
		memset(d, 0x3f, sizeof d);
		memset(v, 0x00, sizeof v);
	}
	void solveDijkstra(int v0, int n) { // 执行主计算任务(使用Dijkstra)
		priority_queue<pair<T, int>, vector<pair<T, int> >, greater<pair<T, int> > >q;
		reset_solver(n); // 自动调用对距离表与访问标识表的清除
		d[v0] = 0;
		q.push(make_pair(0, v0));
		while (q.size()) {
			pair<T, int> p = q.top();
			T dis = p.first; // dis为到当前点的距离
			int pos = p.second; // pos为当前点
			q.pop();
			v[pos] = 1;
			for (int i = 0; i < G[pos].size(); i++) {
				int x = G[pos][i].first; // x为当前枚举边的终点，
				T y = G[pos][i].second; // y为当前枚举边的权值
				if (d[x] > d[pos] + y) {
					d[x] = d[pos] + y;
					if (!v[x])
						q.push(make_pair(d[x], x));
				}
			}
		}
	}
	void solveSPFA(int v0, int n) { // 执行主计算任务(使用SPFA)
		queue <int> q;
		reset_solver(n); // 自动调用对距离表与访问标识表的清除
		d[v0] = 0;
		v[v0] = 1;
		q.push(v0);
		while (q.size()) {
			int p = q.front();
			q.pop();
			v[p] = 0;
			for (int i = 0; i < G[p].size(); i++) {
				int x = G[p][i].first; // x为当前枚举边的终点，
				T y = G[p][i].second; // y为当前枚举边的权值
				if (d[x] > d[p] + y) {
					d[x] = d[p] + y;
					if (!v[x]) q.push(x), v[x]=1;
				}
			}
		}
	}
};
