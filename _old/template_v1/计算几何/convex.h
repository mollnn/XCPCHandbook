db area(vector<point> A) {
	db ans = 0;
	for (int i = 0; i < A.size(); i++) ans += cross(A[i], A[(i + 1) % A.size()]);
	return ans / 2;
}
int checkconvex(vector<point>A) {
	int n = A.size(); A.push_back(A[0]); A.push_back(A[1]);
	for (int i = 0; i < n; i++) if (sign(cross(A[i + 1] - A[i], A[i + 2] - A[i])) == -1) return 0;
	return 1;
}
int contain(vector<point>A, point q) { 
	int pd = 0; A.push_back(A[0]);
	for (int i = 1; i < A.size(); i++) {
		point u = A[i - 1], v = A[i];
		if (onS(u, v, q)) return 1; if (cmp(u.y, v.y) > 0) swap(u, v);
		if (cmp(u.y, q.y) >= 0 || cmp(v.y, q.y) < 0) continue;
		if (sign(cross(u - v, q - v)) < 0) pd ^= 1;
	}
	return pd << 1;
}
vector<point> ConvexHull(vector<point>A, int flag = 1) { 
	int n = A.size(); vector<point>ans(n * 2);
	sort(A.begin(), A.end()); int now = -1;
	for (int i = 0; i < A.size(); i++) {
		while (now > 0 && sign(cross(ans[now] - ans[now - 1], A[i] - ans[now - 1])) < flag) now--;
		ans[++now] = A[i];
	} int pre = now;
	for (int i = n - 2; i >= 0; i--) {
		while (now > pre && sign(cross(ans[now] - ans[now - 1], A[i] - ans[now - 1])) < flag) now--;
		ans[++now] = A[i];
	} ans.resize(now); return ans;
}
db convexDiameter(vector<point>A) {
	int now = 0, n = A.size(); db ans = 0;
	for (int i = 0; i < A.size(); i++) {
		now = max(now, i);
		while (1) {
			db p1 = A[i].dis(A[now % n]), p2 = A[i].dis(A[(now + 1) % n]);
			ans = max(ans, max(p1, p2)); if (p2 > p1) now++; else break;
		}
	}
	return ans;
}
vector<point> convexcut(vector<point>A, point p1, point p2) {
	int n = A.size(); A.push_back(A[0]); vector<point>ans;
	for (int i = 0; i < n; i++) {
		int w1 = clockwise(p1, p2, A[i]), w2 = clockwise(p1, p2, A[i + 1]);
		if (w1 >= 0) ans.push_back(A[i]);
		if (w1 * w2 < 0) ans.push_back(getLL(p1, p2, A[i], A[i + 1]));
	}
	return ans;
}
int checkPoS(vector<point>A, point p1, point p2) {
	// 多边形 A 和直线 ( 线段 )p1->p2 严格相交 , 注释部分为线段
	struct ins {
		point m, u, v;
		int operator < (const ins& k) const { return m < k.m; }
	}; vector<ins>B;
	//if (contain(A,p1)==2||contain(A,p2)==2) return 1;
	vector<point>poly = A; A.push_back(A[0]);
	for (int i = 1; i < A.size(); i++) if (checkLL(A[i - 1], A[i], p1, p2)) {
		point m = getLL(A[i - 1], A[i], p1, p2);
		if (inmid(A[i - 1], A[i], m)/*&&inmid(p1,p2,m)*/) B.push_back((ins) { m, A[i - 1], A[i] });
	}
	if (B.size() == 0) return 0; sort(B.begin(), B.end());
	int now = 1; while (now < B.size() && B[now].m == B[0].m) now++;
	if (now == B.size()) return 0;
	int flag = contain(poly, (B[0].m + B[now].m) / 2);
	if (flag == 2) return 1;
	point d = B[now].m - B[0].m;
	for (int i = now; i < B.size(); i++) {
		if (!(B[i].m == B[i - 1].m) && flag == 2) return 1;
		int tag = sign(cross(B[i].v - B[i].u, B[i].m + d - B[i].u));
		if (B[i].m == B[i].u || B[i].m == B[i].v) flag += tag; else flag += tag * 2;
	}
	//return 0;
	return flag == 2;
}
int checkinp(point r, point l, point m) {
	if (compareangle(l, r)) { return compareangle(l, m) && compareangle(m, r); }
	return compareangle(l, m) || compareangle(m, r);

}
int checkPosFast(vector<point>A, point p1, point p2) { // 快速检查线段是否和多边形严格相交
	if (contain(A, p1) == 2 || contain(A, p2) == 2) return 1; if (p1 == p2) return 0;
	A.push_back(A[0]); A.push_back(A[1]);
	for (int i = 1; i + 1 < A.size(); i++)
		if (checkLL(A[i - 1], A[i], p1, p2)) {
			point now = getLL(A[i - 1], A[i], p1, p2);
			if (inmid(A[i - 1], A[i], now) == 0 || inmid(p1, p2, now) == 0) continue;
			if (now == A[i]) {
				if (A[i] == p2) continue;
				point pre = A[i - 1], ne = A[i + 1];
				if (checkinp(pre - now, ne - now, p2 - now)) return 1;
			}
			else if (now == p1) {
				if (p1 == A[i - 1] || p1 == A[i]) continue;
				if (checkinp(A[i - 1] - p1, A[i] - p1, p2 - p1)) return 1;
			}
			else if (now == p2 || now == A[i - 1]) continue;
			else return 1;
		}
	return 0;
}
// 拆分凸包成上下凸壳 凸包尽量都随机旋转一个角度来避免出现相同横坐标
// 尽量特判只有一个点的情况 凸包逆时针
void getUDP(vector<point>A, vector<point>& U, vector<point>& D) {
	db l = 1e100, r = -1e100;
	for (int i = 0; i < A.size(); i++) l = min(l, A[i].x), r = max(r, A[i].x);
	int wherel, wherer;
	for (int i = 0; i < A.size(); i++) if (cmp(A[i].x, l) == 0) wherel = i;
	for (int i = A.size(); i; i--) if (cmp(A[i - 1].x, r) == 0) wherer = i - 1;
	U.clear(); D.clear(); int now = wherel;
	while (1) { D.push_back(A[now]); if (now == wherer) break; now++; if (now >= A.size()) now = 0; }
	now = wherel;
	while (1) { U.push_back(A[now]); if (now == wherer) break; now--; if (now < 0) now = A.size() - 1; }
}
// 需要保证凸包点数大于等于 3,2 内部 ,1 边界 ,0 外部
int containCoP(const vector<point>& U, const vector<point>& D, point k) {
	db lx = U[0].x, rx = U[U.size() - 1].x;
	if (k == U[0] || k == U[U.size() - 1]) return 1;
	if (cmp(k.x, lx) == -1 || cmp(k.x, rx) == 1) return 0;
	int where1 = lower_bound(U.begin(), U.end(), (point) { k.x, -1e100 }) - U.begin();
	int where2 = lower_bound(D.begin(), D.end(), (point) { k.x, -1e100 }) - D.begin();
	int w1 = clockwise(U[where1 - 1], U[where1], k), w2 = clockwise(D[where2 - 1], D[where2], k);
	if (w1 == 1 || w2 == -1) return 0; else if (w1 == 0 || w2 == 0) return 1; return 2;
}
// d 是方向 , 输出上方切点和下方切点
pair<point, point> getTangentCow(const vector<point>& U, const vector<point>& D, point d) {
	if (sign(d.x) < 0 || (sign(d.x) == 0 && sign(d.y) < 0)) d = d * (-1);
	point whereU, whereD;
	if (sign(d.x) == 0) return mp(U[0], U[U.size() - 1]);
	int l = 0, r = U.size() - 1, ans = 0;
	while (l < r) { int mid = l + r >> 1; if (sign(cross(U[mid + 1] - U[mid], d)) <= 0) l = mid + 1, ans = mid + 1; else r = mid; }
	whereU = U[ans]; l = 0, r = D.size() - 1, ans = 0;
	while (l < r) { int mid = l + r >> 1; if (sign(cross(D[mid + 1] - D[mid], d)) >= 0) l = mid + 1, ans = mid + 1; else r = mid; }
	whereD = D[ans]; return mp(whereU, whereD);
}
// 先检查 contain, 逆时针给出
pair<point, point> getTangentCoP(const vector<point>& U, const vector<point>& D, point k) {
	db lx = U[0].x, rx = U[U.size() - 1].x;
	if (k.x < lx) {
		int l = 0, r = U.size() - 1, ans = U.size() - 1;
		while (l < r) { int mid = l + r >> 1; if (clockwise(k, U[mid], U[mid + 1]) == 1) l = mid + 1; else ans = mid, r = mid; }
		point w1 = U[ans]; l = 0, r = D.size() - 1, ans = D.size() - 1;
		while (l < r) { int mid = l + r >> 1; if (clockwise(k, D[mid], D[mid + 1]) == -1) l = mid + 1; else ans = mid, r = mid; }
		point w2 = D[ans]; return mp(w1, w2);
	}
	else if (k.x > rx) {
		int l = 1, r = U.size(), ans = 0;
		while (l < r) { int mid = l + r >> 1; if (clockwise(k, U[mid], U[mid - 1]) == -1) r = mid; else ans = mid, l = mid + 1; }
		point w1 = U[ans]; l = 1, r = D.size(), ans = 0;
		while (l < r) { int mid = l + r >> 1; if (clockwise(k, D[mid], D[mid - 1]) == 1) r = mid; else ans = mid, l = mid + 1; }
		point w2 = D[ans]; return mp(w2, w1);
	}
	else {
		int where1 = lower_bound(U.begin(), U.end(), (point) { k.x, -1e100 }) - U.begin();
		int where2 = lower_bound(D.begin(), D.end(), (point) { k.x, -1e100 }) - D.begin();
		if ((k.x == lx && k.y > U[0].y) || (where1 && clockwise(U[where1 - 1], U[where1], k) == 1)) {
			int l = 1, r = where1 + 1, ans = 0;
			while (l < r) { int mid = l + r >> 1; if (clockwise(k, U[mid], U[mid - 1]) == 1) ans = mid, l = mid + 1; else r = mid; }
			point w1 = U[ans]; l = where1, r = U.size() - 1, ans = U.size() - 1;
			while (l < r) { int mid = l + r >> 1; if (clockwise(k, U[mid], U[mid + 1]) == 1) l = mid + 1; else ans = mid, r = mid; }
			point w2 = U[ans]; return mp(w2, w1);
		}
		else {
			int l = 1, r = where2 + 1, ans = 0;
			while (l < r) { int mid = l + r >> 1; if (clockwise(k, D[mid], D[mid - 1]) == -1) ans = mid, l = mid + 1; else r = mid; }
			point w1 = D[ans]; l = where2, r = D.size() - 1, ans = D.size() - 1;
			while (l < r) { int mid = l + r >> 1; if (clockwise(k, D[mid], D[mid + 1]) == -1) l = mid + 1; else ans = mid, r = mid; }
			point w2 = D[ans]; return mp(w1, w2);
		}
	}
}
