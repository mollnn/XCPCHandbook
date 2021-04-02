#include <bits/stdc++.h>
using namespace std;
const int SN = 200005;
struct SplayTree {
	int k[SN], sz[SN], cnt[SN], fa[SN], ch[SN][2], ind, root;
	SplayTree() {
		memset(k, 0, sizeof k);
		memset(sz, 0, sizeof sz);
		memset(cnt, 0, sizeof cnt);
		memset(fa, 0, sizeof fa);
		memset(ch, 0, sizeof ch);
		ind = 0; root = 0;
	}
	void pushup(int p) {
		sz[p] = sz[ch[p][0]] + sz[ch[p][1]] + cnt[p];
	}
	void rotate(int p) {
		int q = fa[p], y = fa[q], x = ch[q][1] == p;
		ch[q][x] = ch[p][x ^ 1]; fa[ch[q][x]] = q;
		ch[p][x ^ 1] = q; fa[q] = p; fa[p] = y;
		if (y) ch[y][ch[y][1] == q] = p;
		pushup(q); pushup(p);
	}
	void splay(int x) {
		for (int y; y = fa[x]; rotate(x))
			if (fa[y]) rotate((ch[fa[y]][0] == y) == (ch[y][0] == x) ? y : x);
		root = x;
	}
	int search(int v) {
		int p = root;
		while (p && (k[p] - v)) p = ch[p][k[p] < v];
		return p;
	}
	void insert(int v) {
		if (root == 0) {
			root = ++ind;
			k[root] = v;
			sz[root] = cnt[root] = 1;
		}
		else if (search(v)) {
			int tmp = search(v);
			splay(tmp);
			sz[tmp]++; cnt[tmp]++;
		}
		else {
			int p = root;
			while (p && ch[p][k[p] < v]) p = ch[p][k[p] < v];
			ch[p][k[p] < v] = ++ind;
			fa[ind] = p;
			k[ind] = v; sz[ind] = cnt[ind] = 1;
			splay(ind);
		}
	}
	void remove(int p) {
		if (p == 0) return;
		splay(p);
		if (cnt[p] > 1) { cnt[p]--; sz[p]--; return; }
		int l = ch[p][0], r = ch[p][1];
		fa[l] = fa[r] = 0; ch[p][0] = ch[p][1] = 0;
		if (l == 0) { root = r; return; }
		if (r == 0) { root = l; return; }
		int t = l;
		while (t && ch[t][1]) t = ch[t][1];
		root = l; splay(t);
		ch[t][1] = r; fa[r] = t;
		pushup(t);
	}
	void remove_v(int v) {
		remove(search(v));
	}
	int rank(int p) {
		splay(p);
		return sz[ch[p][0]] + 1;
	}
	int rank_v(int v) {
		return rank(search(v));
	}
	int kth(int p, int k) {
		if (k <= sz[ch[p][0]]) return kth(ch[p][0], k);
		if (k <= sz[ch[p][0]] + cnt[p]) return p;
		else return kth(ch[p][1], k - sz[ch[p][0]] - cnt[p]);
	}
	int kth(int k0) {
		return kth(root, k0);
	}
	int kth_v(int k0) {
		return k[kth(k0)];
	}
	int prefix(int p) {
		splay(p);
		int t = ch[p][0];
		while (t && ch[t][1]) t = ch[t][1];
		return t;
	}
	int prefix_v(int v) {
		insert(v);
		int r_ans = prefix(search(v));
		remove(search(v));
		return k[r_ans];
	}
	int suffix(int p) {
		splay(p);
		int t = ch[p][1];
		while (t && ch[t][0]) t = ch[t][0];
		return t;
	}
	int suffix_v(int v) {
		insert(v);
		int r_ans = suffix(search(v));
		remove(search(v));
		return k[r_ans];
	}
} T;
