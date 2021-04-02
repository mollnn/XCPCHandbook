// Tarjan's algorithm to generate Dominator Tree
//  warning: this algorithm is for normal directed graph 
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int n,m;
struct node{
    vector<int>edge[N];
    inline void add(int u,int v){edge[u].push_back(v);}
}a,b,c,d;
int dfn[N],id[N],fa[N],cnt;
void dfs(int u){
    dfn[u]=++cnt;id[cnt]=u;
    int len=a.edge[u].size();
    for(int i=0;i<len;++i){
        int v=a.edge[u][i];
        if(dfn[v])continue;
        fa[v]=u;dfs(v);
    }
}
int semi[N],idom[N],bel[N],val[N];
inline int find(int x){
    if(x==bel[x])return x;
    int tmp=find(bel[x]);
    if(dfn[semi[val[bel[x]]]]<dfn[semi[val[x]]]) val[x]=val[bel[x]];
    return bel[x]=tmp;
}
inline void tarjan(){
    for(int i=cnt;i>1;--i){
        int u=id[i],len=b.edge[u].size();
        for(int i=0;i<len;++i){
            int v=b.edge[u][i];
            if(!dfn[v])continue;
            find(v);
            if(dfn[semi[val[v]]]<dfn[semi[u]]) semi[u]=semi[val[v]];
        }
        c.add(semi[u],u);
        bel[u]=fa[u];
        u=fa[u];
        len=c.edge[u].size();
        for(int i=0;i<len;++i){
            int v=c.edge[u][i];
            find(v);
            if(semi[val[v]]==u)idom[v]=u;
            else idom[v]=val[v];
        }
    }
    for(int i=2;i<=cnt;++i){
        int u=id[i];
        if(idom[u]!=semi[u]) idom[u]=idom[idom[u]];
    }
}
int ans[N];
void dfs_ans(int u){
    ans[u]=1;
    int len=d.edge[u].size();
    for(int i=0;i<len;++i){
        int v=d.edge[u][i];
        dfs_ans(v);
        ans[u]+=ans[v];
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i){
    	int u,v;
        scanf("%d%d",&u,&v);
        // pay attention to the order
        a.add(u,v);
        b.add(v,u);
    }
    for(int i=1;i<=n;++i) semi[i]=bel[i]=val[i]=i;
    dfs(1);//root id
    tarjan();
    for(int i=2;i<=n;++i) d.add(idom[i],i);//make dominator tree
    dfs_ans(1);
    for(int i=1;i<=n;++i)printf("%d ",ans[i]);
}
