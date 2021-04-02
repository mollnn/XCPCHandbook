vector<line> getHL(vector<line>& L) { //
	sort(L.begin(), L.end()); deque<line> q;
	for (int i = 0; i < (int)L.size(); i++) {
		if (i && sameDir(L[i], L[i - 1])) continue;
		while (q.size() > 1 && !checkpos(q[q.size() - 2], q[q.size() - 1], L[i])) q.pop_back();
		while (q.size() > 1 && !checkpos(q[1], q[0], L[i])) q.pop_front();
		q.push_back(L[i]);
	}
	while (q.size() > 2 && !checkpos(q[q.size() - 2], q[q.size() - 1], q[0])) q.pop_back();
	while (q.size() > 2 && !checkpos(q[1], q[0], q[q.size() - 1])) q.pop_front();
	vector<line>ans; for (int i = 0; i < q.size(); i++) ans.push_back(q[i]);
	return ans;
}
