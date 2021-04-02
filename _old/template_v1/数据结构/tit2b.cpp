#include <bits/stdc++.h>
using namespace std;

const int N = 200000000;

int n, m, t1, t2, t3, t4;
int a[30000005], ch[30000005][2], inner_ind, outer_ind, b[8000005], Ch[8000005][2], ROOT, seq[8000005];

void inner_pushup(int p) {
	a[p] = a[ch[p][0]] + a[ch[p][1]];
}

void inner_modify(int& p, int l, int r, int pos, int key) {
	if (p == 0) p = ++inner_ind;
	if (l == r) {
		a[p] += key;
	}
	else {
		if (pos <= (l + r) / 2) inner_modify(ch[p][0], l, (l + r) / 2, pos, key);
		else inner_modify(ch[p][1], (l + r) / 2 + 1, r, pos, key);
		inner_pushup(p);
	}
}

int inner_query(int p, int l, int r, int ql, int qr) {
	if (l > qr || r < ql) return 0;
	if (l >= ql && r <= qr) return a[p];
	return inner_query(ch[p][0], l, (l + r) / 2, ql, qr) + inner_query(ch[p][1], (l + r) / 2 + 1, r, ql, qr);
}

void outer_modify(int& p, int l, int r, int opos, int ipos, int ikey) {
	if (p == 0) {
		p = ++outer_ind;
	}
	inner_modify(b[p], 1, n, ipos, ikey);
	if (r - l) {
		if (opos <= (l + r) / 2) outer_modify(Ch[p][0], l, (l + r) / 2, opos, ipos, ikey);
		else outer_modify(Ch[p][1], (l + r) / 2 + 1, r, opos, ipos, ikey);
	}
}

void outer_modify(int l, int r, int opos, int ipos, int ikey) {
	outer_modify(ROOT, l, r, opos + 2, ipos, ikey);
}

int outer_query(int p, int l, int r, int ql, int qr, int iql, int iqr) {
	if (l > qr || r < ql) return 0;
	if (l >= ql && r <= qr) return inner_query(b[p], 1, n, iql, iqr);
	return outer_query(Ch[p][0], l, (l + r) / 2, ql, qr, iql, iqr)
+ outer_query(Ch[p][1], (l + r) / 2 + 1, r, ql, qr, iql, iqr);
}

int outer_query(int l, int r, int ql, int qr, int iql, int iqr) {
	return outer_query(ROOT, l, r, ql + 2, qr + 2, iql, iqr);
}

int outer_kth(int p, int l, int r, int k, int iql, int iqr) {
	if (l == r) return r;
	int tmp = 0;
	if (Ch[p][0] && (tmp = inner_query(b[Ch[p][0]], 1, n, iql, iqr)) >= k)
		return outer_kth(Ch[p][0], l, (l + r) / 2, k, iql, iqr);
	else
		return outer_kth(Ch[p][1], (l + r) / 2 + 1, r, k - tmp, iql, iqr);
}

int outer_kth(int l, int r, int k, int iql, int iqr) {
	return outer_kth(ROOT, l, r, k, iql, iqr) - 2;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> t1; seq[i] = t1;
		outer_modify(1, N, t1, i, 1);
	}
	for (int i = 1; i <= m; i++) {
		cin >> t1;
		if (t1 == 1) {
			cin >> t2 >> t3 >> t4;
			cout << outer_query(1, N, 0, t4 - 1, t2, t3) + 1 << endl;
		}
		if (t1 == 2) {
			cin >> t2 >> t3 >> t4;
			cout << outer_kth(1, N, t4, t2, t3) << endl;
		}
		if (t1 == 3) {
			cin >> t2 >> t3;
			outer_modify(1, N, seq[t2], t2, -1);
			outer_modify(1, N, t3, t2, 1);
			seq[t2] = t3;
		}
		if (t1 == 4) {
			cin >> t2 >> t3 >> t4;
			int k = outer_query(1, N, 0, t4 - 1, t2, t3);
			if (k <= 0) cout << -2147483647 << endl;
			else cout << outer_kth(1, N, k, t2, t3) << endl;
		}
		if (t1 == 5) {
			cin >> t2 >> t3 >> t4;
			int k = outer_query(1, N, 0, t4, t2, t3) + 1;
			if (k > (t3 - t2 + 1)) cout << 2147483647 << endl;
			else cout << outer_kth(1, N, k, t2, t3) << endl;
		}
	}
}
