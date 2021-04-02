#include <bits/stdc++.h>
using namespace std;
const int N = 16384, MAXN = 262144;
#define reset(x) memset(x,0,sizeof x)
struct graph {
    int n,m,M,S,T,head[N],cur[N],dep[N],gap[N],q[N];
    long long ans;
    struct ed {
        int to,nxt,val;
    } edge[MAXN];
    void init(int n0,int m0,int S0,int T0) {
        n=n0,m=m0,S=S0,T=T0,M=1,reset(gap);
        reset(head),reset(cur),reset(dep),reset(q);
    }
    void make(int u,int v,int w) {
        edge[++M]=(ed) {v,head[u],w},head[u]=M;
    }
    int dfs(int u,int mx) {
        if (u==T)
            return mx;
        int num=0,f;
        for (int &i=cur[u],v; i; i=edge[i].nxt)
            if (dep[v=edge[i].to]==dep[u]-1 && (f=edge[i].val))
                if (edge[i].val-=(f=dfs(v,min(mx-num,f))), edge[i^1].val+=f, (num+=f)==mx)
                    return num;
        if (!--gap[dep[u]++])
            dep[S]=n+1;
        return ++gap[dep[u]],cur[u]=head[u],num;
    }
    void solve() {
        for (int i=1; i<=n; ++i)
            cur[i]=head[i];
        ans=0;
        for (gap[0]=n; dep[S]<=n; ans+=dfs(S,0x7fffffff));
    }
} g;

int n,m,S,T,t1,t2,t3;
int main() {
    scanf("%d%d%d%d",&n,&m,&S,&T);
    g.init(n,m,S,T);
    for (int i=1; i<=m; ++i)
        scanf("%d%d%d",&t1,&t2,&t3),g.make(t1,t2,t3),g.make(t2,t1,0);
    g.solve();
    printf("%lld\n",g.ans);
}
