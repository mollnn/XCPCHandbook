#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

int seq[100005], s0[100005], n, m, cnta[100005], tmp, root[100005], f[100005], ind, k[1000005], ch[1000005][2], fa[1000005], tsize[1000005], us0[100005], red[100005], mp[1000005], t1, t2, t3;

int ufs_find(int p) {
	int t = p, tt = p, ttt;
	while (t - f[t] && f[t] && t) t = f[t];
	while (tt - f[tt] && f[tt] && tt) ttt = f[tt], f[tt] = t, tt = ttt;
	return t;
}

void ufs_union(int sp, int sq) { // union p to q
	int p = ufs_find(sp), q = ufs_find(sq);
	if (p - q) f[p] = q;
}

void rotate(int p) {
	int q = fa[p], y = fa[q], x = ch[q][1] == p;
	ch[q][x] = ch[p][x ^ 1]; fa[ch[q][x]] = q;
	ch[p][x ^ 1] = q; fa[q] = p; fa[p] = y;
	if (y)if (ch[y][0] == q) ch[y][0] = p;
	else if (ch[y][1] == q) ch[y][1] = p;
}

void splay(int x, int tid) {
	for (int y = fa[x]; y = fa[x]; rotate(x))
		if (fa[y])rotate((ch[y][0] == x) == (ch[fa[y]][0] == y) ? y : x);
	root[tid] = x;
}

void insert(int x, int tid) {
	if (root[tid] == 0) root[tid] = ++ind, k[ind] = x, tsize[tid]++;
	else {
		int p = root[tid], tp = root[tid];
		while (p && tp) p = tp, tp = ch[p][k[p] < x];
		ch[p][k[p] < x] = ++ind; k[ind] = x; fa[ind] = p;
		splay(ind, tid); tsize[tid]++;
	}
}

void merge(int p, int tid) {
	if (p == 0) return;
	insert(k[p], tid);
	if (ch[p][0]) merge(ch[p][0], tid);
	if (ch[p][1]) merge(ch[p][1], tid);
}

void print(int p) {
	if (p == 0) return;
	print(ch[p][0]);
	printf("%d ", k[p]);
	print(ch[p][1]);
}

int findmin(int p) {
	int x = p;
	while (ch[x][0] && x) x = ch[x][0];
	return x;
}

void remove(int p, int tid) {
	if (p == 0)return;
	splay(p, tid);
	int lr = ch[p][0], rr = ch[p][1];
	if (lr == 0) { root[tid] = rr, fa[rr] = 0; return; }
	int tm = lr;
	root[tid] = lr;
	while (tm && ch[tm][1]) tm = ch[tm][1];
	if (tm) splay(tm, tid);
	ch[root[tid]][1] = rr; fa[rr] = root[tid];
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &seq[i]), s0[i] = seq[i];
	sort(seq + 1, seq + n + 1);
	for (int i = 1; i <= n; i++) s0[i] = lower_bound(seq + 1, seq + n + 1, s0[i]) - seq;
	for (int i = 1; i <= n; i++) tmp = s0[i], s0[i] += cnta[s0[i]], cnta[tmp]++;
	for (int i = 1; i <= n; i++) insert(s0[i], i), f[i] = i, us0[s0[i]] = i;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &t1, &t2);
		if (t1 == 1) {
			scanf("%d", &t3);
			if (red[t2] || red[t3]) goto Next;
			t2 = ufs_find(t2); t3 = ufs_find(t3);
			if (tsize[t2] > tsize[t3]) { int tmp = t2; t2 = t3; t3 = tmp; }
			ufs_union(t2, t3); merge(root[t2], t3);
		}
		else {
			if (red[t2]) { printf("-1\n"); goto Next; }
			t2 = ufs_find(t2);
			int t = findmin(root[t2]);
			if (tsize[t2] == 0) { printf("-1\n"); goto Next; }
			printf("%d\n", seq[k[t]]);
			remove(t, t2); red[us0[k[t]]] = 1; tsize[t2]--;
		}
	Next:;
	}
}
