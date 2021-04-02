struct point {
	db x, y;
	point operator + (const point& p1) const { return (point) { p1.x + x, p1.y + y }; }
	point operator - (const point& p1) const { return (point) { x - p1.x, y - p1.y }; }
	point operator * (db p1) const { return (point) { x* p1, y* p1 }; }
	point operator / (db p1) const { return (point) { x / p1, y / p1 }; }
	int operator == (const point& p1) const { return cmp(x, p1.x) == 0 && cmp(y, p1.y) == 0; }
	// 逆时针旋转
	point turn(db p1) { return (point) { x* cos(p1) - y * sin(p1), x* sin(p1) + y * cos(p1) }; }
	point turn90() { return (point) { -y, x }; }
	bool operator < (const point p1) const {
		int a = cmp(x, p1.x);
		if (a == -1) return 1; else if (a == 1) return 0; else return cmp(y, p1.y) == -1;
	}
	db abs() { return sqrt(x * x + y * y); }
	db abs2() { return x * x + y * y; }
	db dis(point p1) { return ((*this) - p1).abs(); }
	point unit() { db w = abs(); return (point) { x / w, y / w }; }
	void scan() { double p1, p2; scanf("%lf%lf", &p1, &p2); x = p1; y = p2; }
	void print() { printf("%.11lf %.11lf\n", x, y); }
	db getw() { return atan2(y, x); }
	point getdel() { if (sign(x) == -1 || (sign(x) == 0 && sign(y) == -1)) return (*this) * (-1); else return (*this); }
	int getP() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) == -1); }
};
int inmid(point p1, point p2, point p3) { return inmid(p1.x, p2.x, p3.x) && inmid(p1.y, p2.y, p3.y); }
db cross(point p1, point p2) { return p1.x * p2.y - p1.y * p2.x; }
db dot(point p1, point p2) { return p1.x * p2.x + p1.y * p2.y; }
db rad(point p1, point p2) { return atan2(cross(p1, p2), dot(p1, p2)); }
// -pi -> pi
int compareangle(point p1, point p2) {
	return p1.getP() < p2.getP() || (p1.getP() == p2.getP() && sign(cross(p1, p2)) > 0);
}
point proj(point p1, point p2, point q) { // q 到直线 p1,p2 的投影
	point k = p2 - p1; return p1 + k * (dot(q - p1, k) / k.abs2());
}
point reflect(point p1, point p2, point q) { return proj(p1, p2, q) * 2 - q; }
int clockwise(point p1, point p2, point p3) {// p1 p2 p3 逆时针 1 顺时针 -1 否则 0
	return sign(cross(p2 - p1, p3 - p1));
}
