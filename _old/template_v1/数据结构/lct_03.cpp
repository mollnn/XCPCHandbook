#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n,m,val[N];

struct LinkCutTree {
    int top, q[N], ch[N][2], fa[N], xr[N], rev[N], s[N], si[N];
    inline void pushup(int x) { // !
        s[x]=s[ch[x][0]]+s[ch[x][1]]+si[x]+1;
    }
    inline void pushdown(int x) {
        if(!rev[x])
            return;
        rev[ch[x][0]]^=1;
        rev[ch[x][1]]^=1;
        rev[x]^=1;
        swap(ch[x][0],ch[x][1]);
    }
    inline bool isroot(int x) {
        return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x;
    }
    inline void rotate(int p) {
        int q=fa[p], y=fa[q], x=ch[fa[p]][1]==p;
        ch[q][x]=ch[p][x^1];
        fa[ch[q][x]]=q;
        ch[p][x^1]=q;
        fa[q]=p;
        fa[p]=y;
        if(y)
            if(ch[y][0]==q)
                ch[y][0]=p;
            else  if(ch[y][1]==q)
                ch[y][1]=p;
        pushup(q);
        pushup(p);
    }
    inline void splay(int x) {
        q[top=1]=x;
        for(int i=x; !isroot(i); i=fa[i])
            q[++top]=fa[i];
        for(int i=top; i; i--)
            pushdown(q[i]);
        for(; !isroot(x); rotate(x))
            if(!isroot(fa[x]))
                rotate((ch[fa[x]][0]==x)==(ch[fa[fa[x]]][0]==fa[x])?fa[x]:x);
    }
    void access(int x) { // !
        for(int t=0; x; t=x,x=fa[x])
            splay(x),si[x]+=s[ch[x][1]],si[x]-=s[ch[x][1]=t],pushup(x);
    }
    void makeroot(int x) {
        access(x);
        splay(x);
        rev[x]^=1;
    }
    int find(int x) {
        access(x);
        splay(x);
        while(ch[x][0])
            x=ch[x][0];
        return x;
    }
    void split(int x,int y) {
        makeroot(x);
        access(y);
        splay(y);
    }
    void cut(int x,int y) { // !
        split(x,y);
        if(ch[y][0]==x)
            ch[y][0]=0, fa[x]=0;
        pushup(y);
    }
    void link(int x,int y) { // !
        split(x,y);
        si[fa[x]=y]+=s[x];
        pushup(y);
    }
} T;

int main() {
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1; i<=n; i++)
        T.s[i]=1;
    for(int i=1; i<=m; i++) {
        string str;
        cin>>str;
        int u,v;
        cin>>u>>v;
        if(str[0]=='A') {
            T.link(u,v);
        } else {
            T.cut(u,v);
            T.makeroot(u);
            T.makeroot(v);
            cout<<T.s[u]*T.s[v]<<endl;
            T.link(u,v);
        }
    }
}
