#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int k[N], sz[N], val[N], mx[N], add[N], ch[N][2], fa[N], rev[N], n, m, t1, t2, t3, t4, ind, root;

void pushup(int p) {
	mx[0] = val[0] = -1e+9;
	sz[p] = sz[ch[p][0]] + sz[ch[p][1]] + 1;
	mx[p] = max(max(mx[ch[p][0]], mx[ch[p][1]]), val[p]);
}

void pushdown(int p) {
	if (rev[p]) {
		rev[ch[p][0]] ^= 1; rev[ch[p][1]] ^= 1;
		rev[p] ^= 1; swap(ch[p][0], ch[p][1]);
	}
	if (add[p]) {
		add[ch[p][0]] += add[p];
		add[ch[p][1]] += add[p];
		val[ch[p][0]] += add[p];
		val[ch[p][1]] += add[p];
		mx[ch[p][0]] += add[p];
		mx[ch[p][1]] += add[p];
		add[p] = 0;
	}
}

void rotate(int p, int& k) {
	int q = fa[p], y = fa[q], x = ch[q][1] == p;
	if (y) pushdown(y);
	pushdown(q); pushdown(p);
	ch[q][x] = ch[p][x ^ 1]; fa[ch[q][x]] = q;
	ch[p][x ^ 1] = q; fa[q] = p; fa[p] = y;
	if (q != k) {
		if (ch[y][0] == q) ch[y][0] = p;
		else if (ch[y][1] == q) ch[y][1] = p;
	}
	else k = p;
	pushup(q); pushup(p);
}

void splay(int x, int& k) {
	for (int y; (y = fa[x]) && (x != k); rotate(x, k))
		if (y != k) rotate((ch[fa[y]][0] == y) == (ch[y][0] == x) ? y : x, k);
}

void splay(int x) {
	splay(x, root);
}

void insert(int v) {
	if (root == 0) {
		root = ++ind;
		k[ind] = v;
		sz[ind] = 1;
	}
	else {
		int p = root;
		while (p && ch[p][k[p] < v]) p = ch[p][k[p] < v];
		ch[p][k[p] < v] = ++ind;
		fa[ind] = p;
		k[ind] = v;
		sz[ind] = 1;
		splay(ind);
	}
}

int kth(int p, int k) {
	if (p == 0 || k == 0) return 0;
	pushdown(p);
	if (k <= sz[ch[p][0]]) return kth(ch[p][0], k);
	if (k == sz[ch[p][0]] + 1) return p;
	return kth(ch[p][1], k - sz[ch[p][0]] - 1);
}

int nodesplit(int l, int r) {
	if (l) {
		splay(l);
		if (r) {
			splay(r, ch[l][1]);
			return ch[r][0];
		}
		else return ch[l][1];
	}
	else {
		if (r) {
			splay(r);
			return ch[r][0];
		}
		else return root;
	}
}

int split(int l, int r) {
	return nodesplit(kth(root, l - 1), kth(root, r + 1));
}

void putadd(int l, int r, int k) {
	int tmp = split(l, r);
	add[tmp] += k; val[tmp] += k; mx[tmp] += k;
}

void reverse(int l, int r) {
	int tmp = split(l, r);
	rev[tmp] ^= 1;
}

int query(int l, int r) {
	int tmp = split(l, r);
	return mx[tmp];
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) insert(i);
	for (int i = 1; i <= m; i++) {
		cin >> t1 >> t2 >> t3;
		if (t1 == 1) {
			cin >> t4;
			putadd(t2, t3, t4);
		}
		if (t1 == 2) {
			reverse(t2, t3);
		}
		if (t1 == 3) {
			cout << query(t2, t3) << endl;
		}
	}
}
