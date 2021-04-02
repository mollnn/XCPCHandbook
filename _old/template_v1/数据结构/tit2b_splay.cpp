struct Splay {
	struct Node {
		Node* fa, * ch[2], ** root;
		int x, size, cnt;
		Node(Node** root, Node* fa, int x) : root(root), fa(fa), x(x), cnt(1), size(1) {
			ch[0] = ch[1] = NULL;
		}
		int relation() {
			return this == fa->ch[0] ? 0 : 1;
		}
		void maintain() {
			size = cnt;
			if (ch[0]) size += ch[0]->size;
			if (ch[1]) size += ch[1]->size;
		}
		void rotate() {
			Node* old = fa;
			int r = relation();
			fa = old->fa;
			if (old->fa) old->fa->ch[old->relation()] = this;
			if (ch[r ^ 1]) ch[r ^ 1]->fa = old;
			old->ch[r] = ch[r ^ 1];
			old->fa = this;
			ch[r ^ 1] = old;
			old->maintain();
			maintain();
			if (fa == NULL)* root = this;
		}
		void splay(Node* target = NULL) {
			while (fa != target) {
				if (fa->fa == target) rotate();
				else if (fa->relation() == relation()) fa->rotate(), rotate();
				else rotate(), rotate();
			}
		}
		Node* pred() {
			Node* v = ch[0];
			while (v->ch[1]) v = v->ch[1];
			return v;
		}
		Node* succ() {
			Node* v = ch[1];
			while (v->ch[0]) v = v->ch[0];
			return v;
		}
		int rank() {
			return ch[0] ? ch[0]->size : 0;
		}
	} *root;
	Splay() : root(NULL) {
		insert(INT_MAX);
		insert(INT_MIN);
	}
	Node* insert(int x) {
		Node** v = &root, * fa = NULL;
		while (*v != NULL && (*v)->x != x) {
			fa = *v;
			fa->size++;
			if (x < fa->x) v = &fa->ch[0];
			else v = &fa->ch[1];
		}
		if (*v != NULL) (*v)->cnt++, (*v)->size++;
		else (*v) = new Node(&root, fa, x);
		(*v)->splay();
		return root;
	}
	Node* find(int x) {
		Node* v = root;
		while (v != NULL && v->x != x) {
			if (x < v->x) v = v->ch[0];
			else v = v->ch[1];
		}
		if (v) v->splay();
		return v;
	}
	void erase(Node* v) {
		Node* pred = v->pred(), * succ = v->succ();
		pred->splay();
		succ->splay(pred);
		if (v->size > 1) {
			v->size--;
			v->cnt--;
		}
		else {
			delete succ->ch[0];
			succ->ch[0] = NULL;
		}
		succ->size--;
		pred->size--;
	}
	void erase(int x) {
		Node* v = find(x);
		if (!v) return;
		erase(v);
	}
	int pred(int x) {
		Node* v = find(x);
		if (v == NULL) {
			v = insert(x);
			int ret = v->pred()->x;
			erase(v);
			return ret;
		}
		else return v->pred()->x;
	}
	int succ(int x) {
		Node* v = find(x);
		if (v == NULL) {
			v = insert(x);
			int ret = v->succ()->x;
			erase(v);
			return ret;
		}
		else return v->succ()->x;
	}
	int rank(int x) {
		Node* v = find(x);
		if (v == NULL) {
			v = insert(x);
			int ret = v->rank();
			erase(v);
			return ret;
		}
		else return v->rank();
	}
	int kth(int k) {
		Node* v = root;
		while (!(k >= v->rank() && k < v->rank() + v->cnt)) {
			if (k < v->rank()) v = v->ch[0];
			else k -= v->rank() + v->cnt, v = v->ch[1];
		}
		v->splay();
		return v->x;
	}
}

Splay tree[200005];
void Modify(int p, int l, int r, int pos, int val) {
	tree[p].insert(val);
	if (l != r) {
		int mid = (l + r) / 2;
		if (pos <= mid) Modify(p * 2, l, mid, pos, val);
		else Modify(p * 2 + 1, mid + 1, r, pos, val);
	}
}

void Modify_Erase(int p, int l, int r, int pos, int val) {
	tree[p].erase(val);
	if (l != r) {
		int mid = (l + r) / 2;
		if (pos <= mid) Modify_Erase(p * 2, l, mid, pos, val);
		else Modify_Erase(p * 2 + 1, mid + 1, r, pos, val);
	}
}

int QueryCount(int p, int l, int r, int ql, int qr, int val) {
	if (l > qr || r < ql) return 0;
	if (l >= ql && r <= qr) return tree[p].rank(val) - 1;
	int mid = (l + r) / 2;
	return QueryCount(p * 2, l, mid, ql, qr, val) + QueryCount(p * 2 + 1, mid + 1, r, ql, qr, val);
}

int getPrefix(int p, int l, int r, int ql, int qr, int val) {
	if (l > qr || r < ql) return INT_MIN;
	if (l >= ql && r <= qr) return tree[p].pred(val);
	int mid = (l + r) / 2;
	return max(getPrefix(p * 2, l, mid, ql, qr, val), getPrefix(p * 2 + 1, mid + 1, r, ql, qr, val));
}

int getSuffix(int p, int l, int r, int ql, int qr, int val) {
	if (l > qr || r < ql) return INT_MAX;
	if (l >= ql && r <= qr) return tree[p].succ(val);
	int mid = (l + r) / 2;
	return min(getSuffix(p * 2, l, mid, ql, qr, val), getSuffix(p * 2 + 1, mid + 1, r, ql, qr, val));
}

int n, m, a[100005];

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) Modify(1, 1, n, i, a[i]);
	for (int i = 1; i <= m; i++) {
		int opt, l, r, x, pos;
		cin >> opt;
		if (opt == 1) {
			cin >> l >> r >> x;
			cout << QueryCount(1, 1, n, l, r, x) + 1 << endl;
		}
		else if (opt == 2) {
			cin >> l >> r >> x;
			int L = -1e+8 - 1, R = 1e+8 + 1;
			while (R - L) {
				int M = (L + R) >> 1;
				if (QueryCount(1, 1, n, l, r, M) < x) L = M + 1;
				else R = M;
			}
			cout << L - 1 << endl;
		}
		else if (opt == 3) {
			cin >> pos >> x;
			Modify_Erase(1, 1, n, pos, a[pos]);
			a[pos] = x;
			Modify(1, 1, n, pos, x);
		}
		else if (opt == 4) {
			cin >> l >> r >> x;
			cout << getPrefix(1, 1, n, l, r, x) << endl;
		}
		else if (opt == 5) {
			cin >> l >> r >> x;
			cout << getSuffix(1, 1, n, l, r, x) << endl;
		}
	}
}
