// 1D
const int N = 10000;
int ar[N]; // index: 1 ~ N
int lowbit(int t) { return t & (-t); }
void add(int i, int v) {
	for (; i < N; ar[i] += v, i += lowbit(i));
}
int sum(int i) {
	int s = 0;
	for (; i > 0; s += ar[i], i -= lowbit(i));
	return s;
}

// 2D
int c[N][N]; int Row, Col;
inline int lowbit(const int& x) {// x > 0
	return x & (-x);
}
int Sum(int i, int j) {
	int tmp, sum = 0;
	while (i > 0) {
		tmp = j;
		while (tmp > 0) {
			sum += c[i][tmp];
			tmp -= lowbit(tmp);
		}
		i -= lowbit(i);
	}
	return sum;
}
void Update(int i, int j, int num) {
	int tmp;
	while (i <= Row) {
		tmp = j;
		while (tmp <= Col) {
			c[i][tmp] += num;
			tmp += lowbit(tmp);
		}
		i += lowbit(i);
	}
}
