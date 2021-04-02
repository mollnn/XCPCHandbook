template <class T> class Graph_SCC { // 用Tarjan算法求强连通分量并建出分量图.
public: // 使用前务必对n进行设定！
	vector <int> g[MAX_NODE], sta, comp[MAX_NODE]; // g为原图
	T val[MAX_NODE]; // val存原图中点权值
	int n, is[MAX_NODE], dfn[MAX_NODE], low[MAX_NODE], ic[MAX_NODE], ind, cnt;
	vector <T>* G; // 返回指针
	T* key; // 返回指针
	void make_edge(int t1, int t2) { // 造边（有向）
		g[t1].push_back(t2);
	}
	void reset_graph() { // 用于清除图邻接表
		for (int i = 0; i <= n; i++)
			g[i].clear(), comp[n].clear();
		memset(val, 0, sizeof val);
	}
	void reset_solver(int n) { // 对各种数组的清除 如果改变了类型，该函数可能需要重写！
		memset(is, 0, sizeof is);
		memset(dfn, 0, sizeof dfn);
		memset(low, 0, sizeof low);
		memset(ic, 0, sizeof ic);
		ind = cnt = 0;
	}
	void tarjan(int p) {
		is[p] = 2;
		dfn[p] = low[p] = ++ind;
		sta.push_back(p);
		for (int i = 0; i < g[p].size(); i++)
			if (dfn[g[p][i]] == 0) {
				tarjan(g[p][i]);
				low[p] = min(low[p], low[g[p][i]]);
			}
			else {
				if (is[g[p][i]] == 2)
					low[p] = min(low[p], dfn[g[p][i]]);
			}
		if (low[p] == dfn[p]) {
			++cnt;
			for (int i = 0; i != p;) {
				i = sta[sta.size() - 1];
				sta.pop_back();
				is[i] = 1;
				ic[i] = cnt;
				key[cnt] += val[i];
				comp[cnt].push_back(i);
			}
		}
	}
	int Solve(vector <T>* _G, T* _key) { // 主计算函数，缩点并造出分量图传回G处，key存新图中点权
		// 注意！使用前务必对n进行设定！
		G = _G;
		key = _key;
		reset_solver(n);
		for (int i = 1; i <= n; i++)
			if (dfn[i] == 0)
				tarjan(i);
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < g[i].size(); j++)
				if (ic[i] - ic[g[i][j]])
					G[ic[i]].push_back(ic[g[i][j]]);
		return cnt; //返回值为分量图的点数
	}
};
