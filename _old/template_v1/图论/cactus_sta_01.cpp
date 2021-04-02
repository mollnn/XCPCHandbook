// We have a cactus G=(V,E), where |V|=n, |E|=m
// We have q queries. Each as (u,v), querying the SP between u and v.
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define RG register
#define MAX 20000
inline int read()
{
    RG int x=0,t=1;RG char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}
struct Line{int v,next,w;};
struct Link
{
    Line e[111111];
    int h[MAX],cnt;
    inline void Add(int u,int v,int w)
    {
        e[++cnt]=(Line){v,h[u],w};h[u]=cnt;
        e[++cnt]=(Line){u,h[v],w};h[v]=cnt;
    }
}T,G;
int n;
struct RST
{
    int fa[MAX],size[MAX],hson[MAX],top[MAX],dep[MAX],dis[MAX];
    int dfn[MAX],tim,ln[MAX],cir[MAX];
    bool zn[MAX];
    void dfs1(int u,int ff)
    {
        fa[u]=ff;size[u]=1;dep[u]=dep[ff]+1;
        for(int i=T.h[u];i;i=T.e[i].next)
        {
            int v=T.e[i].v;if(v==ff)continue;
            dis[v]=dis[u]+T.e[i].w;
            dfs1(v,u);size[u]+=size[v];
            if(size[v]>size[hson[u]])hson[u]=v;
        }
    }
    void dfs2(int u,int tp)
    {
        top[u]=tp;dfn[u]=++tim,ln[tim]=u;
        if(hson[u])dfs2(hson[u],tp);
        for(int i=T.h[u];i;i=T.e[i].next)
            if(T.e[i].v!=fa[u]&&T.e[i].v!=hson[u])
                dfs2(T.e[i].v,T.e[i].v);
    }
    int LCA(int u,int v)
    {
        while(top[u]^top[v])dep[top[u]]<dep[top[v]]?v=fa[top[v]]:u=fa[top[u]];
        return dep[u]<dep[v]?u:v;
    }
    int Jump(int u,int LCA)
    {
        int ret;
        while(top[u]!=top[LCA])
            ret=top[u],u=fa[top[u]];
        return u==LCA?ret:ln[dfn[LCA]+1];
    }
    int Query(int u,int v)
    {
        int lca=LCA(u,v);
        if(lca<=n)return dis[u]+dis[v]-2*dis[lca];
        int uu=Jump(u,lca),vv=Jump(v,lca);
        int d1=dis[uu]-dis[lca],d2=dis[vv]-dis[lca];
        if(!zn[uu])d1=cir[lca]-d1;if(!zn[vv])d2=cir[lca]-d2;
        return dis[u]-dis[uu]+dis[v]-dis[vv]+min(abs(d1-d2),cir[lca]-abs(d1-d2));
    }
}RST;
int dfn[MAX],low[MAX],tim,tp[MAX],dep[MAX];
int fa[MAX];
ll dis[MAX];
int S[MAX],tot,m,Q;
void Build(int u,int y,int d)
{
    int top=dep[y]-dep[u]+1,sum=d,Dis=0;
    for(int i=y;i!=u;i=fa[i])S[top--]=i,sum+=dis[i]-dis[fa[i]];
    ++tot;S[1]=u;top=dep[y]-dep[u]+1;RST.cir[tot]=sum;
    for(int i=1;i<=top;++i)
    {
        int D=min(Dis,sum-Dis);
        T.Add(tot,S[i],D);
        RST.zn[S[i]]=(D==Dis);
        Dis+=dis[S[i+1]]-dis[S[i]];
    }
}
void Tarjan(int u,int ff)
{
    dfn[u]=low[u]=++tim;dep[u]=dep[ff]+1;fa[u]=ff;
    for(int i=G.h[u];i;i=G.e[i].next)
    {
        int v=G.e[i].v;if(v==ff)continue;
        if(!dfn[v])
        {
            dis[v]=dis[u]+G.e[i].w;
            Tarjan(v,u);low[u]=min(low[u],low[v]);
        }
        else low[u]=min(low[u],dfn[v]);
        if(dfn[u]<low[v])T.Add(u,v,G.e[i].w);
    }
    for(int i=G.h[u];i;i=G.e[i].next)
    {
        int v=G.e[i].v;if(v==ff)continue;
        if(fa[v]!=u&&dfn[u]<dfn[v])Build(u,v,G.e[i].w);
    }
}
int main()
{
    tot=n=read();m=read();Q=read();G.cnt=1;
    for(int i=1;i<=m;++i)
    {
        int u=read(),v=read(),w=read();
        G.Add(u,v,w);
    }
    Tarjan(1,0);
    RST.dfs1(1,0);RST.dfs2(1,1);
    while(Q--)printf("%d\n",RST.Query(read(),read()));
    return 0;
}
