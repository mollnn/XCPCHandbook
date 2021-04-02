// n <= 5000  m <= 5e+5
// MLE warning
#include<bits/stdc++.h>
#define N 16800000
#define M 1000006
using namespace std;
char ch;
inline void rd(int &x)
{
    for(;(ch=getchar()-'0')<0||ch>9;);
    for(x=ch;(ch=getchar()-'0')>=0&&ch<=9;
    x=(x<<3)+(x<<1)+ch);
}
bool intr[M],del[N],gdel[N];
int n,m,lev[M],hd[M][16],
Nxt[N],To[N],
gt,et=1,mp[5003][5003],nxt[N],to[N],
c[N][2],f[N],se[N],st[N],Se[N],St[N];

inline void upd(int x)
{
    Se[x]=se[x]+Se[c[x][0]]+Se[c[x][1]],
    St[x]=st[x]+St[c[x][0]]+St[c[x][1]];
}
inline void rotate(int x,bool t)
{
    register int y=f[x];
    f[y]?c[f[y]][c[f[y]][1]==y]=x:0;
    f[x]=f[y],c[y][t^1]=c[x][t];
    f[c[x][t]]=y,c[x][t]=y,f[y]=x;
    upd(y),upd(x);
}
inline void splay(int x,int to)
{
    int y;bool t1,t2;
    while(f[x]^to)
    {
        t1=c[y=f[x]][0]==x,t2=c[f[y]][0]==y;
        if(f[y]==to)
        {rotate(x,t1);return;}
        t1^t2?rotate(x,t1):rotate(y,t2);
        rotate(x,t2);
    }
}
inline void Gins(int u,int v,int l)
{
    hd[mp[u][v]][l]=++gt;
    u=l*n+u;
    splay(u,0),st[u]++,upd(u);
    nxt[gt]=nxt[u],nxt[u]=gt,to[gt]=v;
}
inline void Ins(int &x,int y,bool t)
{
    if(!y)return;
    while(c[x][t])x=c[x][t];
    c[x][t]=y,f[y]=x;
    splay(y,0),x=y;
}
inline int getr(int x)
{
    splay(x,0);
    while(c[x][0])x=c[x][0];
    splay(x,0);return x;
}
inline void reroot(int u)
{
    if(getr(u)==u)return;
    splay(u,0);
    register int x=c[u][0];c[u][0]=0,upd(u);
    Ins(u,x,1);
}
inline void link(int u,int v,int l)
{
    register int x=hd[mp[u][v]][l];
    intr[mp[u][v]]=intr[mp[v][u]]=1;
    u=l*n+u,v=l*n+v;
    reroot(v),splay(u,0),splay(v,0);
    se[u]++,se[v]++,upd(v),
    Nxt[x]=Nxt[u],Nxt[u]=x,To[x]=v,
    Nxt[x^1]=Nxt[v],Nxt[v]=x^1,To[x^1]=u;
    Ins(v,x,0),Ins(v,x^1,1);
    gdel[x]=gdel[x^1]=1;
    x=c[u][1];while(c[x][0])x=c[x][0];
    if(x)
    {
        splay(x,u);
        c[x][0]=v,f[v]=x,upd(x);
    }
    else c[u][1]=v,f[v]=u;
    upd(u);
}
inline void cut(int u,int v,int l)
{
    register int x=hd[mp[u][v]][l];
    u=l*n+u,v=l*n+v;
    reroot(u);
    splay(x,0);
    splay(x^1,x);
    f[c[x^1][0]]=f[c[x^1][1]]=f[c[x][0]]=0;
    splay(u,0),se[u]--,upd(u);
    Ins(u,c[x^1][1],1);
    splay(v,0),se[v]--,upd(v);
}
inline void pushup(int u,int v,int l,bool t)
{
    del[hd[mp[u][v]][l]]=del[hd[mp[v][u]][l]]=1;
    register int x=mp[u][v];
    lev[x]=lev[x^1]=l;
    Gins(u,v,l),Gins(v,u,l);
    if(t)link(u,v,l);
}
void dfse(int x)
{
    if(!Se[x])return;
    if(se[x])
    {
        for(int i=Nxt[x];i;i=Nxt[i])
        if(!del[i])pushup((x-1)%n+1,(To[i]-1)%n+1,(x-1)/n,1);
        Nxt[x]=se[x]=0;
    }
    dfse(c[x][0]),dfse(c[x][1]),upd(x);
}
bool dfst(int x,int y)
{
    if(!St[x])return 0;
    if(st[x])
    {
        for(int i=nxt[x];i;i=nxt[i])
        {
            if(!(del[i]|gdel[i]))
            {
                register int l=(x-1)/n;
                if(getr(l*n+to[i])^y)
                pushup((x-1)%n+1,(to[i]-1)%n+1,(x-1)/n,0);
                else
                {
                    upd(x),x=(x-1)%n+1;
                    for(int j=0;j<=l;j++)
                    link(x,to[i],j);
                    return 1;
                }
            }
            st[x]--,nxt[x]=nxt[i];
        }
    }
    St[x]=0;
    if(dfst(c[x][0],y))return 1;
    return dfst(c[x][1],y);
}
inline bool rec(int u,int v,int l)
{
    u=l*n+u,v=l*n+v;
    splay(u,0),splay(v,0);
    if(St[u]>St[v])swap(u,v);
    register int x=getr(v);
    dfse(u);
    return dfst(u,x);
}
int op,u,v,x,ans;
int main()
{
    rd(n),rd(m),gt=n<<4|1;
    while(m--)
    {
        rd(op),rd(u),rd(v),u^=ans,v^=ans;
        if(!op)
        {
            mp[u][v]=++et,mp[v][u]=++et;
            Gins(u,v,0),Gins(v,u,0);
            if(getr(u)^getr(v))link(u,v,0);
        }
        else if(op>1)
        getr(u)==getr(v)?puts("Y"),ans=u:(puts("N"),ans=v);
        else
        {
            x=mp[u][v];
            for(int i=0;i<=lev[x];i++)
            del[hd[x][i]]=del[hd[x^1][i]]=1;
            if(intr[x])
            {
                for(int i=lev[x];i>=0;i--)
                cut(u,v,i);
                for(int i=lev[x];i>=0;i--)
                if(rec(u,v,i))break;
            }
        }
    }
}
