struct circle {
	point o; db r;
	void scan() { o.scan(); scanf("%lf", &r); }
	int inside(point k) { return cmp(r, o.dis(k)); }
};
int checkposCC(circle p1, circle p2) {// 返回两个圆的公切线数量
	if (cmp(p1.r, p2.r) == -1) swap(p1, p2);
	db dis = p1.o.dis(p2.o);  int w1 = cmp(dis, p1.r + p2.r), w2 = cmp(dis, p1.r - p2.r);
	if (w1 > 0) return 4; else if (w1 == 0) return 3; else if (w2 > 0) return 2;
	else if (w2 == 0) return 1; else return 0;
}
vector<point> getCL(circle p1, point p2, point p3) { // 沿着 p2->p3 方向给出 , 相切给出两个
	point k = proj(p2, p3, p1.o); db d = p1.r * p1.r - (k - p1.o).abs2();
	if (sign(d) == -1) return {};
	point del = (p3 - p2).unit() * sqrt(max((db)0.0, d)); return { k - del,k + del };
}
vector<point> getCC(circle p1, circle p2) {// 沿圆 p1 逆时针给出 , 相切给出两个
	int pd = checkposCC(p1, p2); if (pd == 0 || pd == 4) return {};
	db a = (p2.o - p1.o).abs2(), cosA = (p1.r * p1.r + a - p2.r * p2.r) / (2 * p1.r * sqrt(max(a, (db)0.0)));
	db b = p1.r * cosA, c = sqrt(max((db)0.0, p1.r * p1.r - b * b));
	point k = (p2.o - p1.o).unit(), m = p1.o + k * b, del = k.turn90() * c;
	return { m - del,m + del };
}
vector<point> TangentCP(circle p1, point p2) {// 沿圆 p1 逆时针给出
	db a = (p2 - p1.o).abs(), b = p1.r * p1.r / a, c = sqrt(max((db)0.0, p1.r * p1.r - b * b));
	point k = (p2 - p1.o).unit(), m = p1.o + k * b, del = k.turn90() * c;
	return { m - del,m + del };
}
vector<line> TangentoutCC(circle p1, circle p2) {
	int pd = checkposCC(p1, p2); if (pd == 0) return {};
	if (pd == 1) { point k = getCC(p1, p2)[0]; return { (line) { k,k } }; }
	if (cmp(p1.r, p2.r) == 0) {
		point del = (p2.o - p1.o).unit().turn90().getdel();
		return { (line) { p1.o - del * p1.r,p2.o - del * p2.r },(line) { p1.o + del * p1.r,p2.o + del * p2.r } };
	}
	else {
		point p = (p2.o * p1.r - p1.o * p2.r) / (p1.r - p2.r);
		vector<point>A = TangentCP(p1, p), B = TangentCP(p2, p);
		vector<line>ans; for (int i = 0; i < A.size(); i++) ans.push_back((line) { A[i], B[i] });
		return ans;
	}
}
vector<line> TangentinCC(circle p1, circle p2) {
	int pd = checkposCC(p1, p2); if (pd <= 2) return {};
	if (pd == 3) { point k = getCC(p1, p2)[0]; return { (line) { k,k } }; }
	point p = (p2.o * p1.r + p1.o * p2.r) / (p1.r + p2.r);
	vector<point>A = TangentCP(p1, p), B = TangentCP(p2, p);
	vector<line>ans; for (int i = 0; i < A.size(); i++) ans.push_back((line) { A[i], B[i] });
	return ans;
}
vector<line> TangentCC(circle p1, circle p2) {
	int flag = 0; if (p1.r < p2.r) swap(p1, p2), flag = 1;
	vector<line>A = TangentoutCC(p1, p2), B = TangentinCC(p1, p2);
	for (line k : B) A.push_back(k);
	if (flag) for (line& k : A) swap(k[0], k[1]);
	return A;
}
db getarea(circle p1, point p2, point p3) {
	// 圆 p1 与三角形 p2 p3 p1.o 的有向面积交
	point k = p1.o; p1.o = p1.o - k; p2 = p2 - k; p3 = p3 - k;
	int pd1 = p1.inside(p2), pd2 = p1.inside(p3);
	vector<point>A = getCL(p1, p2, p3);
	if (pd1 >= 0)
		if (pd2 >= 0) return cross(p2, p3) / 2;
		else return p1.r * p1.r * rad(A[1], p3) / 2 + cross(p2, A[1]) / 2;
	else if (pd2 >= 0)
		return p1.r * p1.r * rad(p2, A[0]) / 2 + cross(A[0], p3) / 2;
	else
		if (cmp(p1.r, disSP(p2, p3, p1.o)) <= 0) return p1.r * p1.r * rad(p2, p3) / 2;
		else return cross(A[0], A[1]) / 2 + p1.r * p1.r * (rad(p2, A[0]) + rad(A[1], p3)) / 2;
}
circle getcircle(point p1, point p2, point p3) {
	db a1 = p2.x - p1.x, b1 = p2.y - p1.y, c1 = (a1 * a1 + b1 * b1) / 2;
	db a2 = p3.x - p1.x, b2 = p3.y - p1.y, c2 = (a2 * a2 + b2 * b2) / 2;
	db d = a1 * b2 - a2 * b1;
	point o = (point){ p1.x + (c1 * b2 - c2 * b1) / d,p1.y + (a1 * c2 - a2 * c1) / d };

	return (circle) { o, p1.dis(o) };
}
circle getScircle(vector<point> A) {
	random_shuffle(A.begin(), A.end());
	circle ans = (circle){ A[0],0 };
	for (int i = 1; i < A.size(); i++)
		if (ans.inside(A[i]) == -1) {
			ans = (circle){ A[i],0 };
			for (int j = 0; j < i; j++)
				if (ans.inside(A[j]) == -1) {
					ans.o = (A[i] + A[j]) / 2; ans.r = ans.o.dis(A[i]);
					for (int k = 0; k < j; k++)
						if (ans.inside(A[k]) == -1)
							ans = getcircle(A[i], A[j], A[k]);
				}
		}
	return ans;
}
