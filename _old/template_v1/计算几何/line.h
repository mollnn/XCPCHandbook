int checkLL(point p1, point p2, point p3, point p4) {// 求直线 (L) 线段 (S)p1,p2 和 p3,p4 的交点
	return cmp(cross(p3 - p1, p4 - p1), cross(p3 - p2, p4 - p2)) != 0;
}
point getLL(point p1, point p2, point p3, point p4) {
	db w1 = cross(p1 - p3, p4 - p3), w2 = cross(p4 - p3, p2 - p3); return (p1 * w2 + p2 * w1) / (w1 + w2);
}
int intersect(db l1, db r1, db l2, db r2) {
	if (l1 > r1) swap(l1, r1); if (l2 > r2) swap(l2, r2); return cmp(r1, l2) != -1 && cmp(r2, l1) != -1;
}
int checkSS(point p1, point p2, point p3, point p4) {
	return intersect(p1.x, p2.x, p3.x, p4.x) && intersect(p1.y, p2.y, p3.y, p4.y) &&
		sign(cross(p3 - p1, p4 - p1)) * sign(cross(p3 - p2, p4 - p2)) <= 0 &&
		sign(cross(p1 - p3, p2 - p3)) * sign(cross(p1 - p4, p2 - p4)) <= 0;
}
db disSP(point p1, point p2, point q) {
	point p3 = proj(p1, p2, q);
	if (inmid(p1, p2, p3)) return q.dis(p3); else return min(q.dis(p1), q.dis(p2));
}
db disSS(point p1, point p2, point p3, point p4) {
	if (checkSS(p1, p2, p3, p4)) return 0;
	else return min(min(disSP(p1, p2, p3), disSP(p1, p2, p4)), min(disSP(p3, p4, p1), disSP(p3, p4, p2)));
}
int onS(point p1, point p2, point q) { return inmid(p1, p2, q) && sign(cross(p1 - q, p2 - p1)) == 0; }
struct line {
	// p[0]->p[1]
	point p[2];
	line(point p1, point p2) { p[0] = p1; p[1] = p2; }
	point& operator [] (int k) { return p[k]; }
	int include(point k) { return sign(cross(p[1] - p[0], k - p[0])) > 0; }
	point dir() { return p[1] - p[0]; }
	line push() { // 向外 ( 左手边 ) 平移 eps
		const db eps = 1e-6;
		point delta = (p[1] - p[0]).turn90().unit() * eps;
		return { p[0] - delta,p[1] - delta };
	}
};
point getLL(line p1, line p2) { return getLL(p1[0], p1[1], p2[0], p2[1]); }
int parallel(line p1, line p2) { return sign(cross(p1.dir(), p2.dir())) == 0; }
int sameDir(line p1, line p2) { return parallel(p1, p2) && sign(dot(p1.dir(), p2.dir())) == 1; }
int operator < (line p1, line p2) {
	if (sameDir(p1, p2)) return p2.include(p1[0]);
	return compareangle(p1.dir(), p2.dir());
}
int checkpos(line p1, line p2, line p3) { return p3.include(getLL(p1, p2)); }
