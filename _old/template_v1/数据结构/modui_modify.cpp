// In each query, How many sub-interval whose XOR sum is 0
#define reset(x) memset(x,0,sizeof(x))

struct Query {
	long long l, r, t;
	long long result;
} query[100005];

long long n, m, tot, a[100005], l, r, pos, change[100005], be[100005], s[100005], pLeft, pRight, pTime, bs[100005];
long long cnt[4000005], ans;

bool cmp(Query& a, Query& b) {
	return be[a.l] == be[b.l] ? (be[a.r] == be[b.r] ? a.t < b.t : a.r < b.r) : (a.l < b.l);
}

bool cmp_back(Query& a, Query& b) {
	return a.t < b.t;
}

void pushByPosi(long long posi) {
	ans += cnt[s[posi]];
	cnt[s[posi]]++;
}

void popByPosi(long long posi) {
	cnt[s[posi]]--;
	ans -= cnt[s[posi]];
}

void pushByTime(long long tim) {
	if (change[tim]) {
		long long p = change[tim];
		swap(a[p], a[p + 1]);
		if (pLeft <= p && p <= pRight) {
			cnt[s[p]]--;
			ans -= cnt[s[p]];
		}
		s[p] = s[p - 1] ^ s[p + 1] ^ s[p];
		if (pLeft <= p && p <= pRight) {
			ans += cnt[s[p]];
			cnt[s[p]]++;
		}
	}
}

void popByTime(long long tim) {
	pushByTime(tim);
}

int main() {
	ios::sync_with_stdio(false);
	while (cin >> n >> m) {
		tot = l = r = pos = pLeft = pRight = pTime = ans = 0;
		reset(a); reset(change); reset(be); reset(s); reset(cnt); reset(query);
		for (long long i = 1; i <= n; i++) cin >> a[i];
		for (long long i = 1; i <= m; i++) {
			long long type;
			cin >> type;
			if (type == 1) {
				cin >> l >> r;
				query[++tot].l = l;
				query[tot].r = r;
				query[tot].t = i;
			}
			if (type == 2) {
				cin >> pos;
				change[i] = pos;
			}
		}
		long long unitSize = pow(tot, 0.6667);
		for (long long i = 1; i <= tot; i++) {
			be[i] = i / unitSize + 1;
		}
		sort(query + 1, query + tot + 1, cmp);
		for (long long i = 1; i <= n; i++)
			s[i] = s[i - 1] ^ a[i];
		pLeft = 1;
		pRight = 0;
		pTime = 0;
		//cnt[0] = 1;
		for (long long i = 1; i <= tot; i++) {
			long long qLeft = query[i].l - 1, qRight = query[i].r, qTime = query[i].t;
			while (qTime > pTime) pushByTime(++pTime);
			while (qTime < pTime) popByTime(pTime--);
			while (qLeft < pLeft) pushByPosi(--pLeft);
			while (qRight > pRight) pushByPosi(++pRight);
			while (qLeft > pLeft) popByPosi(pLeft++);
			while (qRight < pRight) popByPosi(pRight--);

			query[i].result = (qRight - qLeft + 1) * (qRight - qLeft) / 2 - ans;
		}

		sort(query + 1, query + tot + 1, cmp_back);
		for (long long i = 1; i <= tot; i++)
			cout << query[i].result << endl;
	}
}
