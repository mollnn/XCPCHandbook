#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<vector>
using namespace std;
const int maxn=200001;
struct edge{int from,to,dist;};
int ____________a,b,c,d,n,m,u,v,val,dis[maxn];
vector<edge>edges;
vector<int>g[maxn];
bool vis[maxn],flag;
void spfa(int u){
    vis[u]=1;
    for(int i=0;i<g[u].size();i++){
        edge &e=edges[g[u][i]];
        int v=e.to;
        if(dis[v]>dis[u]+e.dist){
            dis[v]=dis[u]+e.dist;
            if(vis[v]){
                flag=1;
                return ;}
            spfa(v);}}
    vis[u]=0; }
inline void init()
{
    for(int i=1;i<=n;i++) g[i].clear();
    edges.clear();
    memset(dis,0,sizeof(dis));
    memset(vis,0,sizeof(vis));
}
inline void addedge()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&val);
        edges.push_back((edge){u,v,val});
        g[u].push_back(edges.size()-1);
        if(val>0)
        {
        edges.push_back((edge){v,u,val});
        g[v].push_back(edges.size()-1);
        }
    }
}
inline bool judge()
{
    flag=0;
    for(int i=1;i<=n;i++)
    {
        spfa(i);
        if(flag) return 1;
    }
    return 0;
}
inline void solve()
{
    int t;
    cin>>t;
    while(t--)
    {
        init();
        addedge();
        if(judge()) cout<<"YE5"<<endl;
        else cout<<"N0"<<endl;
    }
}
int main(){
    solve();
    return 0;
}
