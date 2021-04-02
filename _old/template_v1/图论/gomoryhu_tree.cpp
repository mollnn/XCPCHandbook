#include <bits/stdc++.h>

using namespace std;

const int maxn=6e2;
const int maxm=2e3;
const int inf=2047483647;

int n,m,q;

inline int read() {
    int a=0;char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9') a=(a<<1)+(a<<3)+c-'0',c=getchar();
    return a;
}

//for the target graph
int edgeNum,head[maxn],to[maxm<<1],nxt[maxm<<1],w[maxm<<1];

inline void add(int u,int v,int c) {
    nxt[++edgeNum]=head[u];head[u]=edgeNum;
    to[edgeNum]=v;w[edgeNum]=c;
}

int cnt,p[maxn],tmp[maxn],S[maxn];
//cnt stands for the first few Uni-blocks
//p[i] represents the number of the point on the i-th point
//tmp array is used to copy the sort p array
//S[u] indicates the Unicom block number where u is in

struct GHT {
    int s,t,maxFlow,cur[maxn];

    int edgeNum=-1,head[maxn],to[maxm<<1],nxt[maxm<<1];
    int w[maxm<<1],f[maxm<<1];

    GHT() {memset(head,-1,sizeof(head));}

    inline void add_edge(int u,int v,int c) {
        nxt[++edgeNum]=head[u];head[u]=edgeNum;
        to[edgeNum]=v;w[edgeNum]=c;
    }

    int dep[maxn],gap[maxn];

    inline void bfs() {
        memset(dep,0,sizeof(dep));memset(gap,0,sizeof(gap));
        dep[t]=gap[1]=1;queue<int> Q;Q.push(t);
        while(!Q.empty()) { int u=Q.front();Q.pop();
            for(int i=head[u];i!=-1;i=nxt[i]) if(!dep[to[i]])
                ++gap[dep[to[i]]=dep[u]+1],Q.push(to[i]);
        }
    }

    int dfs(int u,int lastFlow) {
        int used=0,minFlow=0;
        if(u==t) {maxFlow+=lastFlow;return lastFlow;}
        for(int &i=cur[u];i!=-1;i=nxt[i])
            if(f[i]&&dep[to[i]]+1==dep[u])
                if(minFlow=dfs(to[i],min(lastFlow-used,f[i])))
                {   f[i]-=minFlow;f[i^1]+=minFlow;
                    if((used+=minFlow)==lastFlow) return used;
                }
        if(!(--gap[dep[u]++])) dep[s]=n+1;
        ++gap[dep[u]];return used;
    }

    inline int ISAP(int x,int y) {
        for(register int i=0;i<=edgeNum;++i) f[i]=w[i];
        maxFlow=0;s=x;t=y;bfs();while(dep[s]<=n) {
            for(register int i=0;i<=n;++i) cur[i]=head[i];
            dfs(s,inf);
        }return maxFlow;
    }

    void dfs(int u) { S[u]=cnt;
        for(int i=head[u];i!=-1;i=nxt[i])
            if(f[i]&&S[to[i]]!=cnt) dfs(to[i]);
    }

    void build(int l,int r) {
        if(l>=r) return ; // Exit with only one point
        int x=p[l],y=p[l+1],cut=ISAP(x,y),L=l,R=r;
        ++cnt;dfs(x);add(x,y,cut);add(y,x,cut);
        for(register int i=l;i<=r;++i) tmp[S[p[i]]==cnt?L++:R--]=p[i];
        for(register int i=l;i<=r;++i) p[i]=tmp[i]; //copy back
        build(l,L-1);build(R+1,r);
    }
}T;

int dep[maxn],fa[maxn][9],Min[maxn][9];

void dfs(int u,int fat) {
    for(register int i=1;i<=8;++i)
        fa[u][i]=fa[fa[u][i-1]][i-1],
        Min[u][i]=min(Min[u][i-1],Min[fa[u][i-1]][i-1]);
    for(int i=head[u];i;i=nxt[i]) if(to[i]!=fat) {
        Min[to[i]][0]=w[i];fa[to[i]][0]=u;
        dep[to[i]]=dep[u]+1;dfs(to[i],u);
    }
}

inline int getCut(int x,int y) {
    int ans=inf;if(dep[x]<dep[y]) x^=y^=x^=y;
    for(register int i=9;i>=0;--i)
        if(dep[fa[x][i]]>=dep[y])
            ans=min(ans,Min[x][i]),x=fa[x][i];
    if(x!=y) {
        for(register int i=9;i>=0;--i)
            if(fa[x][i]!=fa[y][i])
                ans=min(ans,min(Min[x][i],Min[y][i])),
                x=fa[x][i],y=fa[y][i];
        ans=min(ans,min(Min[x][0],Min[y][0]));
    }return ans;
}

int main() {
    n=read();m=read();
    for(register int i=1;i<=n;++i) p[i]=i;
    for(register int i=1;i<=m;++i) {
        int u=read(),v=read(),c=read();
        T.add_edge(u,v,c);T.add_edge(v,u,c);
    }T.build(1,n);dep[1]=1;dfs(1,0);q=read();
    for(register int i=1;i<=q;++i) {
        int u=read(),v=read();
        printf("%d\n",getCut(u,v));
    }return 0;
}
