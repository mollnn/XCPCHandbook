// INPUT (1e+6 ok)
// [Num of varibles] [Num of conditions]
// [i,a,j,b]  xi=a or xj=b  a,b in {0,1}
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define reset(a) memset((a),0,sizeof((a)))
using namespace std;
static char buf[100000],*pa,*pd;
#define gc pa==pd&&(pd=(pa=buf)+fread(buf,1,100000,stdin),pa==pd)?EOF:*pa++
inline int read(){
    register int x(0);register char c(gc);
    while(c>'9'||c<'0')c=gc;
    while(c>='0'&&c<='9')x=x*10+c-48,c=gc;
    return x;
}
const int N=4001000;
struct edge{
    int to,next;
}e[N];
int head[N],tot,HEAD[N];
int n,m,cnt,turn[N],belong[N],vis[N];
void add(int x,int y){
    e[++tot].to=y;e[tot].next=head[x];head[x]=tot;
    e[++tot].to=x;e[tot].next=HEAD[y];HEAD[y]=tot;
}
void dfs1(int u){
    int i;
    vis[u]=1;
    for(i=head[u];i;i=e[i].next)
        if(!vis[e[i].to])
            dfs1(e[i].to);
    turn[++cnt]=u;
}
void dfs2(int u){
    belong[u]=cnt;vis[u]=1;
    for(int i=HEAD[u];i;i=e[i].next)
        if(!vis[e[i].to])
            dfs2(e[i].to);
}
void kosaraju(){
    for(int i=1;i<=2*n;i++)
        if(!vis[i])dfs1(i);
    reset(vis);cnt=0;
    for(int i=2*n;i>=1;i--)
        if(!vis[turn[i]])
            cnt++,dfs2(turn[i]);
}
int main(){
    n=read();m=read();
    register int i,x,y,f1,f2;
    for(i=1;i<=m;i++){
        x=read();f1=read();y=read();f2=read();
        add(x+n*(f1&1),y+n*(f2^1));
        add(y+n*(f2&1),x+n*(f1^1));
    }
    kosaraju();
    for(i=1;i<=n;i++)
        if(belong[i]==belong[i+n]){
            cout<<"IMPOSSIBLE";return 0;
        }
    cout<<"POSSIBLE\n";
    for(i=1;i<=n;i++){
        cout<<(belong[i]>belong[i+n])<<' ';
    }
    return 0;
}
