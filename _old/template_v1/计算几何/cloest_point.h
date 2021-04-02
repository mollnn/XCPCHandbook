db closepoint(vector<point>& A, int l, int r) {
	if (r - l <= 5) {
		db ans = 1e20;
		for (int i = l; i <= r; i++) for (int j = i + 1; j <= r; j++) ans = min(ans, A[i].dis(A[j]));
		return ans;
	}
	int mid = l + r >> 1; db ans = min(closepoint(A, l, mid), closepoint(A, mid + 1, r));
	vector<point>B; for (int i = l; i <= r; i++) if (abs(A[i].x - A[mid].x) <= ans) B.push_back(A[i]);
	sort(B.begin(), B.end(), [](point p1, point p2) {return p1.y < p2.y; });
	for (int i = 0; i < B.size(); i++) for (int j = i + 1; j < B.size() && B[j].y - B[i].y < ans; j++) ans = min(ans, B[i].dis(B[j]));
	return ans;
}
