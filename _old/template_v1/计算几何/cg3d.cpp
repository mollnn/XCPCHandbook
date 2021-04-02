struct P3 {
	db x, y, z;
	P3 operator + (P3 p1) { return (P3) { x + p1.x, y + p1.y, z + p1.z }; }
	P3 operator - (P3 p1) { return (P3) { x - p1.x, y - p1.y, z - p1.z }; }
	P3 operator * (db p1) { return (P3) { x* p1, y* p1, z* p1 }; }
	P3 operator / (db p1) { return (P3) { x / p1, y / p1, z / p1 }; }
	db abs2() { return x * x + y * y + z * z; }
	db abs() { return sqrt(x * x + y * y + z * z); }
	P3 unit() { return (*this) / abs(); }
	int operator < (const P3 p1) const {
		if (cmp(x, p1.x) != 0) return x < p1.x;
		if (cmp(y, p1.y) != 0) return y < p1.y;
		return cmp(z, p1.z) == -1;
	}
	int operator == (const P3 p1) {
		return cmp(x, p1.x) == 0 && cmp(y, p1.y) == 0 && cmp(z, p1.z) == 0;
	}
	void scan() {
		double p1, p2, p3; scanf("%lf%lf%lf", &p1, &p2, &p3);
		x = p1; y = p2; z = p3;
	}
};

P3 cross(P3 p1, P3 p2) { return (P3) { p1.y* p2.z - p1.z * p2.y, p1.z* p2.x - p1.x * p2.z, p1.x* p2.y - p1.y * p2.x }; }
db dot(P3 p1, P3 p2) { return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z; }
//p=(3,4,5),l=(13,19,21),theta=85 ans=(2.83,4.62,1.77)
P3 turn3D(db p1, P3 l, P3 p) {
	l = l.unit(); P3 ans; db c = cos(p1), s = sin(p1);
	ans.x = p.x * (l.x * l.x * (1 - c) + c) + p.y * (l.x * l.y * (1 - c) - l.z * s) + p.z * (l.x * l.z * (1 - c) + l.y * s);
	ans.y = p.x * (l.x * l.y * (1 - c) + l.z * s) + p.y * (l.y * l.y * (1 - c) + c) + p.z * (l.y * l.z * (1 - c) - l.x * s);
	ans.z = p.x * (l.x * l.z * (1 - c) - l.y * s) + p.y * (l.y * l.z * (1 - c) + l.x * s) + p.z * (l.x * l.x * (1 - c) + c);
	return ans;
}
typedef vector<P3> VP;
typedef vector<VP> VVP;
db Acos(db x) { return acos(max(-(db)1, min(x, (db)1))); }
// 球面距离 , 圆心原点 , 半径 1
db Odist(P3 a, P3 b) { db r = Acos(dot(a, b)); return r; }
db r; P3 rnd;
vector<db> solve(db a, db b, db c) {
	db r = sqrt(a * a + b * b), th = atan2(b, a);
	if (cmp(c, -r) == -1) return { 0 };
	else if (cmp(r, c) <= 0) return { 1 };
	else {
		db tr = pi - Acos(c / r); return { th + pi - tr,th + pi + tr };
	}
}
vector<db> jiao(P3 a, P3 b) {
	// dot(rd+x*cos(t)+y*sin(t),b) >= cos(r)
	if (cmp(Odist(a, b), 2 * r) > 0) return { 0 };
	P3 rd = a * cos(r), z = a.unit(), y = cross(z, rnd).unit(), x = cross(y, z).unit();
	vector<db> ret = solve(-(dot(x, b) * sin(r)), -(dot(y, b) * sin(r)), -(cos(r) - dot(rd, b)));
	return ret;
}
db norm(db x, db l = 0, db r = 2 * pi) { // change x into [l,r)
	while (cmp(x, l) == -1) x += (r - l); while (cmp(x, r) >= 0) x -= (r - l);
	return x;
}
db disLP(P3 p1, P3 p2, P3 q) {
	return (cross(p2 - p1, q - p1)).abs() / (p2 - p1).abs();
}
db disLL(P3 p1, P3 p2, P3 p3, P3 p4) {
	P3 dir = cross(p2 - p1, p4 - p3); if (sign(dir.abs()) == 0) return disLP(p1, p2, p3);
	return fabs(dot(dir.unit(), p1 - p2));
}
VP getFL(P3 p, P3 dir, P3 p1, P3 p2) {
	db a = dot(p2 - p, dir), b = dot(p1 - p, dir), d = a - b;
	if (sign(fabs(d)) == 0) return {};
	return { (p1 * a - p2 * b) / d };
}
VP getFF(P3 p1, P3 dir1, P3 p2, P3 dir2) {// 返回一条线
	P3 e = cross(dir1, dir2), v = cross(dir1, e);
	db d = dot(dir2, v); if (sign(abs(d)) == 0) return {};
	P3 q = p1 + v * dot(dir2, p2 - p1) / d; return { q,q + e };
}
// 3D Covex Hull Template
db getV(P3 p1, P3 p2, P3 p3, P3 p4) { // get the Volume
	return dot(cross(p2 - p1, p3 - p1), p4 - p1);
}
db rand_db() { return 1.0 * rand() / RAND_MAX; }
VP convexHull2D(VP A, P3 dir) {
	P3 x = { (db)rand(),(db)rand(),(db)rand() }; x = x.unit();
	x = cross(x, dir).unit(); P3 y = cross(x, dir).unit();
	P3 vec = dir.unit() * dot(A[0], dir);
	vector<point>B;
	for (int i = 0; i < A.size(); i++) B.push_back((point) { dot(A[i], x), dot(A[i], y) });
	B = ConvexHull(B); A.clear();
	for (int i = 0; i < B.size(); i++) A.push_back(x * B[i].x + y * B[i].y + vec);
	return A;
}
namespace CH3 {
	VVP ret; set<pair<int, int> >e;
	int n; VP p, q;
	void wrap(int a, int b) {
		if (e.find({ a,b }) == e.end()) {
			int c = -1;
			for (int i = 0; i < n; i++) if (i != a && i != b) {
				if (c == -1 || sign(getV(q[c], q[a], q[b], q[i])) > 0) c = i;
			}
			if (c != -1) {
				ret.push_back({ p[a],p[b],p[c] });
				e.insert({ a,b }); e.insert({ b,c }); e.insert({ c,a });
				wrap(c, b); wrap(a, c);
			}
		}
	}
	VVP ConvexHull3D(VP _p) {
		p = q = _p; n = p.size();
		ret.clear(); e.clear();
		for (auto& i : q) i = i + (P3) { rand_db() * 1e-4, rand_db() * 1e-4, rand_db() * 1e-4 };
		for (int i = 1; i < n; i++) if (q[i].x < q[0].x) swap(p[0], p[i]), swap(q[0], q[i]);
		for (int i = 2; i < n; i++) if ((q[i].x - q[0].x) * (q[1].y - q[0].y) > (q[i].y - q[0].y) * (q[1].x - q[0].x)) swap(q[1], q[i]), swap(p[1], p[i]);
		wrap(0, 1);
		return ret;
	}
}
VVP reduceCH(VVP A) {
	VVP ret; map<P3, VP> M;
	for (VP nowF : A) {
		P3 dir = cross(nowF[1] - nowF[0], nowF[2] - nowF[0]).unit();
		for (P3 p1 : nowF) M[dir].pb(p1);
	}
	for (pair<P3, VP> nowF : M) ret.pb(convexHull2D(nowF.se, nowF.fi));
	return ret;
}
//  把一个面变成 ( 点 , 法向量 ) 的形式
pair<P3, P3> getF(VP F) {
	return mp(F[0], cross(F[1] - F[0], F[2] - F[0]).unit());
}
// 3D Cut 保留 dot(dir,x-p)>=0 的部分
VVP ConvexCut3D(VVP A, P3 p, P3 dir) {
	VVP ret; VP sec;
	for (VP nowF : A) {
		int n = nowF.size(); VP ans; int dif = 0;
		for (int i = 0; i < n; i++) {
			int d1 = sign(dot(dir, nowF[i] - p));
			int d2 = sign(dot(dir, nowF[(i + 1) % n] - p));
			if (d1 >= 0) ans.pb(nowF[i]);
			if (d1 * d2 < 0) {
				P3 q = getFL(p, dir, nowF[i], nowF[(i + 1) % n])[0];
				ans.push_back(q); sec.push_back(q);
			}
			if (d1 == 0) sec.push_back(nowF[i]); else dif = 1;
			dif |= (sign(dot(dir, cross(nowF[(i + 1) % n] - nowF[i], nowF[(i + 1) % n] - nowF[i]))) == -1);
		}
		if (ans.size() > 0 && dif) ret.push_back(ans);
	}
	if (sec.size() > 0) ret.push_back(convexHull2D(sec, dir));
	return ret;
}
db vol(VVP A) {
	if (A.size() == 0) return 0; P3 p = A[0][0]; db ans = 0;
	for (VP nowF : A)
		for (int i = 2; i < nowF.size(); i++)
			ans += abs(getV(p, nowF[0], nowF[i - 1], nowF[i]));
	return ans / 6;
}
VVP init(db INF) {
	VVP pss(6, VP(4));
	pss[0][0] = pss[1][0] = pss[2][0] = { -INF, -INF, -INF };
	pss[0][3] = pss[1][1] = pss[5][2] = { -INF, -INF, INF };
	pss[0][1] = pss[2][3] = pss[4][2] = { -INF, INF, -INF };
	pss[0][2] = pss[5][3] = pss[4][1] = { -INF, INF, INF };
	pss[1][3] = pss[2][1] = pss[3][2] = { INF, -INF, -INF };
	pss[1][2] = pss[5][1] = pss[3][3] = { INF, -INF, INF };
	pss[2][2] = pss[4][3] = pss[3][1] = { INF, INF, -INF };
	pss[5][0] = pss[4][0] = pss[3][0] = { INF, INF, INF };
	return pss;
}
