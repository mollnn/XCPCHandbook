#include <cstdio>
#include <algorithm>
#include <vector>

inline int read()
{
    int data = 0, w = 1; char ch = getchar();
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') w = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') data = data * 10 + (ch ^ 48), ch = getchar();
    return data * w;
}

const int N(205), M(10010);
struct vector { int x, y; }; vector ans = (vector) {(int) 1e9, (int) 1e9};
inline vector operator - (const vector &lhs, const vector &rhs)
    { return (vector) {lhs.x - rhs.x, lhs.y - rhs.y}; }
inline int operator * (const vector &lhs, const vector &rhs)
    { return lhs.x * rhs.y - lhs.y * rhs.x; }
void chkmin(vector &x, vector y)
{
    long long _x = 1ll * x.x * x.y, _y = 1ll * y.x * y.y;
    if (_x > _y || (_x == _y && x.x > y.x)) x = y;
}

int n, m, fa[N], rnk[N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int merge(int x, int y)
{
    x = find(x), y = find(y);
    return (rnk[x] == rnk[y] ? fa[x] = y, ++rnk[y] :
            (rnk[x] < rnk[y] ? fa[x] = y : fa[y] = x));
}

struct edge { int x, y, a, b, w; } e[M];
inline int operator < (const edge &lhs, const edge &rhs) { return lhs.w < rhs.w; }
vector Kruskal()
{
    vector res = (vector) {0, 0}; int cnt = 0;
    for (int i = 1; i <= n; i++) fa[i] = i, rnk[i] = 1;
    std::sort(e + 1, e + m + 1);
    for (int i = 1; i <= m && cnt < n - 1; i++)
    {
        int x = find(e[i].x), y = find(e[i].y);
        if (x != y) merge(x, y), res.x += e[i].a, res.y += e[i].b, ++cnt;
    }
    return res;
}

void solve(const vector &A, const vector &B)
{
    for (int i = 1; i <= m; i++)
        e[i].w = e[i].a * (A.y - B.y) + e[i].b * (B.x - A.x);
    vector C = Kruskal(); chkmin(ans, C);
    if ((B - A) * (C - A) >= 0) return;
    solve(A, C), solve(C, B);
}

int main()
{
    n = read(), m = read();
    for (int i = 1; i <= m; i++)
        e[i] = (edge) {read() + 1, read() + 1, read(), read(), 0};
    for (int i = 1; i <= m; i++) e[i].w = e[i].a;
    vector A = Kruskal(); chkmin(ans, A);
    for (int i = 1; i <= m; i++) e[i].w = e[i].b;
    vector B = Kruskal(); chkmin(ans, B);
    solve(A, B); printf("%d %d\n", ans.x, ans.y);
    return 0;
}
