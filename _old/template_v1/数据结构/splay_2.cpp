#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
int k[N], sz[N], ch[N][2], fa[N], n, m, t1, t2, t3, t4, rev[N], ind, root;

void pushup(int p) {
	sz[p] = sz[ch[p][0]] + sz[ch[p][1]] + 1;
}

void pushdown(int p) {
	if (rev[p]) {
		rev[ch[p][0]] ^= 1;
		rev[ch[p][1]] ^= 1;
		rev[p] ^= 1;
		swap(ch[p][0], ch[p][1]);
	}
}

void rotate(int p, int& k) {
	int q = fa[p], y = fa[q], x = ch[q][1] == p;
	if (y) pushdown(y);
	pushdown(q); pushdown(p);
	ch[q][x] = ch[p][x ^ 1]; fa[ch[q][x]] = q;
	ch[p][x ^ 1] = q; fa[q] = p; fa[p] = y;
	if (q != k) {
		if (y)if (ch[y][0] == q) ch[y][0] = p;
		else if (ch[y][1] == q) ch[y][1] = p;
	}
	else k = p;
	pushup(q); pushup(p);
}

void splay(int x, int& k) {
	for (int y = fa[x]; x != k; rotate(x, k), y = fa[x])
		if (y != k)
			rotate((ch[fa[y]][0] == y) == (ch[y][0] == x) ? y : x, k);
}

void insert(int v) {
	if (root == 0) {
		root = ++ind;
		k[root] = v;
		sz[root] = 1;
	}
	else {
		int p = root;
		while (p && ch[p][k[p] < v])
			p = ch[p][k[p] < v];
		ch[p][k[p] < v] = ++ind;
		fa[ind] = p;
		sz[ind] = 1;
		k[ind] = v;
		splay(ind, root);
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
		splay(l, root);
		if (r) {
			splay(r, ch[l][1]);
			return ch[r][0];
		}
		else return ch[l][1];
	}
	else
		if (r) {
			splay(r, root);
			return ch[r][0];
		}
		else return root;
}

int split(int l, int r) {
	return nodesplit(kth(root, l - 1), kth(root, r + 1));
}

void reverse(int l, int r) {
	int tmp = split(l, r);
	rev[tmp] ^= 1;
}

void print(int p) {
	if (p == 0) return;
	pushdown(p);
	print(ch[p][0]);
	cout << k[p] << " ";
	print(ch[p][1]);
}

void print() {
	print(root);
	cout << endl;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) insert(i);
	for (int i = 1; i <= m; i++)
		cin >> t1 >> t2,
		reverse(t1, t2);
	print();
}
