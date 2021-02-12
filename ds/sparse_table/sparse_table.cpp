struct st
{
    int a[N][21];
    void build(int *src, int n)
    {
        for (int i = 1; i <= n; i++)
            a[i][0] = src[i];
        for (int i = 1; i <= 20; i++)
            for (int j = 1; j <= n - (1 << i) + 1; j++)
                a[j][i] = max(a[j][i - 1], a[j + (1 << (i - 1))][i - 1]);
    }
    int query(int l, int r)
    {
        int j = log2(r - l + 1); // MAY BE ACCED
        return max(a[l][j], a[r - (1 << j) + 1][j]);
    }
};
